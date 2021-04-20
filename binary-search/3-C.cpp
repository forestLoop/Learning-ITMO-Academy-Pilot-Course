// C. Cows in Stalls
// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/C

#include <bits/stdc++.h>

using namespace std;

int findLargestMinDist(const vector<int> stalls, const int k) {
    const auto n = stalls.size();
    auto canArrange = [&stalls, k](int dist) {
        int cnt = 0, lastStall = -1e9;
        for (const auto pos : stalls) {
            if (pos - lastStall >= dist) {
                cnt++;
                lastStall = pos;
            }
            if (cnt >= k) {
                return true;
            }
        }
        return false;
    };
    int lo = 1, hi = 1e9;
    while (lo + 1 < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (canArrange(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k) {
        vector<int> stalls(n);
        for (auto i = 0; i < n; i++) {
            cin >> stalls[i];
        }
        cout << findLargestMinDist(stalls, k) << endl;
    }
    return 0;
}
