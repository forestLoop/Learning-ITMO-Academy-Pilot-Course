// A. Maximum Average Segment
// https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/A

#include <bits/stdc++.h>

using namespace std;

pair<int, int> locateMaxSegment(const vector<int> &arr, const int d) {
    const int n = arr.size();
    auto canSegment = [&arr, n, d](double avg, bool needResult) -> pair<bool, pair<int, int>> {
        vector<double> prefixSum(n + 1), prefixMin(n + 1);
        prefixSum[0] = 0;
        prefixMin[0] = 0;
        for (auto i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + (arr[i] - avg);
            prefixMin[i + 1] = min(prefixMin[i], prefixSum[i + 1]);
        }
        for (auto j = n - 1; j >= d - 1; j--) {
            if (prefixMin[j + 1 - d] <= prefixSum[j + 1]) {
                auto i = j + 1 - d;
                if (needResult) {
                    while (prefixSum[i] > prefixSum[j + 1]) {
                        i--;
                    }
                }
                return {true, {i, j}};
            }
        }
        return {false, {0, 0}};
    };
    double lo = 0.0, hi = 101.0;
    const int iterations = 25;
    for (auto i = 0; i < iterations; i++) {
        auto mid = lo + (hi - lo) / 2;
        if (canSegment(mid, false).first) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return canSegment(lo, true).second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, d;
    while (cin >> n >> d) {
        vector<int> arr(n);
        for (auto i = 0; i < n; i++) {
            cin >> arr[i];
        }
        auto res = locateMaxSegment(arr, d);
        cout << res.first + 1 << " " << res.second + 1 << endl;
    }
    return 0;
}
