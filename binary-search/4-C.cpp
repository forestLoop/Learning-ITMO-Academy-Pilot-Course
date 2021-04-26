// C. Pair Selection
// https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/C

#include <bits/stdc++.h>

using namespace std;

double findMaxAvg(const vector<pair<int, int>> &pairs, const int k) {
    const auto n = pairs.size();
    auto canSelect = [&pairs, n, k](double avg) {
        vector<double> arr(n);
        for (auto i = 0; i < n; i++) {
            arr[i] = avg * pairs[i].second - pairs[i].first;
        }
        // find top-k in O(n) time
        nth_element(arr.begin(), arr.begin() + k - 1, arr.end());
        double acc = 0.0;
        for (auto i = 0; i < k; i++) {
            acc += arr[i];
        }
        return acc <= 0;
    };
    double lo = 9.9e-6, hi = 1e5;
    const auto iterations = 70;
    for (auto i = 0; i < iterations; i++) {
        auto mid = lo + (hi - lo) / 2;
        if (canSelect(mid)) {
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
        vector<pair<int, int>> pairs(n);
        for (auto i = 0; i < n; i++) {
            cin >> pairs[i].first >> pairs[i].second;
        }
        cout << setprecision(20) << findMaxAvg(pairs, k) << endl;
    }
    return 0;
}
