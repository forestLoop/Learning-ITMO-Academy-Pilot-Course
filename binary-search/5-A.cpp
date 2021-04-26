// A. K-th Number in the Union of Segments
// https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/A

#include <bits/stdc++.h>

using namespace std;

int findKth(const vector<pair<int, int>> &segments, const int k) {
    auto hasLessThanKElements = [&segments, k](long long x) {
        long long cnt = 0;
        for (const auto &seg : segments) {
            if (x > seg.first) {
                cnt += min(x - seg.first, (long long)seg.second - seg.first + 1);
            }
            if (cnt > k) {
                return false;
            }
        }
        return true;
    };
    long long lo = -2e9, hi = 2e9 + 1;
    while (lo + 1 < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (hasLessThanKElements(mid)) {
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
        vector<pair<int, int>> segments(n);
        for (auto i = 0; i < n; i++) {
            cin >> segments[i].first >> segments[i].second;
        }
        cout << findKth(segments, k) << endl;
    }
    return 0;
}
