// B. Ropes
// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/B

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> ropes(n);
        for (int i = 0; i < n; i++) {
            cin >> ropes[i];
        }
        auto canCut = [&ropes, k](double x) {
            int cnt = 0;
            for (const auto &r : ropes) {
                cnt += floor(r / x);
                if (cnt >= k) {
                    return true;
                }
            }
            return false;
        };
        double lo = 0.0, hi = 1e7 + 1;
        const int iterations = 50;  // 1e7 / 1e-6 = 30, make it 50 for safety
        for (int i = 0; i < iterations; i++) {
            auto mid = lo + (hi - lo) / 2;
            if (canCut(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        cout << setprecision(20) << lo << endl;
    }
}
