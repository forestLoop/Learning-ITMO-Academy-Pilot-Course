// D. Minimum maximum on the Path
// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D

#include <bits/stdc++.h>

using namespace std;

vector<int> findMinPath(const vector<vector<pair<int, int>>> &graph, int edgeLimit, int minWeight, int maxWeight) {
    auto n = graph.size() - 1;
    std::function<bool(int, vector<int> &, set<int> &, map<int, int> &)> dfs;
    dfs = [&graph, n, edgeLimit, &dfs](int weightLimit, vector<int> &trace, set<int> &seen, map<int, int> &bestHistory) -> bool {
        auto currentNode = trace[trace.size() - 1];
        // use bestHistory to prune search space:
        // if currentNode has been visited and in that visit, that trace is better (i.e. smaller) than this trace
        // then obviously, this search is unnecessary, just drop it
        if (bestHistory.find(currentNode) != bestHistory.end() && bestHistory[currentNode] <= trace.size()) {
            return false;
        }
        bestHistory[currentNode] = trace.size();
        if (currentNode == n) {
            return true;
        }
        if (trace.size() >= edgeLimit + 1) {
            return false;
        }
        for (const auto &edge : graph[currentNode]) {
            if (edge.second > weightLimit || seen.find(edge.first) != seen.end()) {
                continue;
            }
            trace.push_back(edge.first);
            seen.insert(edge.first);
            if (dfs(weightLimit, trace, seen, bestHistory)) {
                return true;
            }
            seen.erase(edge.first);
            trace.pop_back();
        }
        return false;
    };
    auto canArrive = [&dfs](int weightLimit) {
        vector<int> trace{1};
        set<int> seen{1};
        map<int, int> best;
        return dfs(weightLimit, trace, seen, best);
    };
    if (!canArrive(maxWeight)) {  // it's impossible to find a path
        return vector<int>();
    }
    auto lo = minWeight - 1, hi = maxWeight;
    while (lo + 1 < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (canArrive(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    vector<int> trace{1};
    set<int> seen{1};
    map<int, int> best;
    dfs(hi, trace, seen, best);
    return trace;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, d;
    while (cin >> n >> m >> d) {
        vector<vector<pair<int, int>>> graph(n + 1);
        int minWeight = 1e9, maxWeight = 0;  // to help reduce the search space
        for (auto i = 0; i < m; i++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            graph[from].push_back({to, weight});
            minWeight = min(minWeight, weight);
            maxWeight = max(maxWeight, weight);
        }
        auto res = findMinPath(graph, d, minWeight, maxWeight);
        if (res.size() == 0) {
            cout << -1 << endl;
        } else {
            cout << res.size() - 1 << endl;
            for (const auto x : res) {
                cout << x << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
