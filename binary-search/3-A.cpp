// A.Get together
// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/A

#include <bits/stdc++.h>

using namespace std;

double findMinTime(const vector<int> &x, const vector<int> &v) {
    const auto n = x.size();
    auto canMeet = [&x, &v, n](double time) {
        // initially, the valid range should be the whole range
        double left = -1e9, right = 1e9;
        for (auto i = 0; i < n; i++) {
            auto l = x[i] - time * v[i], r = x[i] + time * v[i];
            if (l > right || r < left) {
                // no overlaping -> impossible for i-th citien to arrive in time
                return false;
            }
            // update the valid range
            left = max(left, l);
            right = min(right, r);
        }
        return true;
    };
    double lo = -0.1, hi = 1e9;
    const auto iterations = 100;  // at least log(2)(1e9 / 1e-6)
    for (auto i = 0; i < iterations; i++) {
        auto mid = lo + (hi - lo) / 2;
        if (canMeet(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return hi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<int> x(n), v(n);
        for (auto i = 0; i < n; i++) {
            cin >> x[i] >> v[i];
        }
        cout << setprecision(20) << findMinTime(x, v) << endl;
    }
    return 0;
}
