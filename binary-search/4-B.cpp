// B. Minimum Average Path
// https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/B

#include <bits/stdc++.h>

using namespace std;

vector<int> findMinAvgPath(const vector<vector<pair<int, int>>> &edges, const int n) {
    auto canReach = [&edges, n](double avg, bool needTrace) -> pair<bool, vector<int>> {
        vector<double> dp(n + 1, 1126);
        vector<int> prev(n + 1, -1);
        dp[1] = 0.0;
        for (auto i = 1; i <= n; i++) {
            if (i != 1 && prev[i] == -1) {  // this node is unreachable
                continue;
            }
            for (const auto &edge : edges[i]) {
                if (dp[i] + edge.second - avg < dp[edge.first]) {
                    dp[edge.first] = dp[i] + edge.second - avg;
                    prev[edge.first] = i;
                }
            }
            if (dp[n] <= 0) {
                break;
            }
        }
        vector<int> trace;
        if (needTrace && dp[n] <= 0) {
            trace.push_back(n);
            while (prev[trace[trace.size() - 1]] != -1) {
                trace.push_back(prev[trace[trace.size() - 1]]);
            }
            reverse(trace.begin(), trace.end());
        }
        return {dp[n] <= 0, trace};
    };
    double lo = -0.1, hi = 100.1;
    const auto iterations = 30;
    for (auto i = 0; i < iterations; i++) {
        auto mid = lo + (hi - lo) / 2;
        if (canReach(mid, false).first) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return canReach(hi, true).second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int, int>>> edges(n + 1);
        for (auto i = 0; i < m; i++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            edges[from].push_back({to, weight});
        }
        auto trace = findMinAvgPath(edges, n);
        cout << trace.size() - 1 << endl;
        for (const auto &x : trace) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
