// D. Children Holiday
// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/D

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    while (cin >> m >> n) {
        vector<int> t(n), z(n), y(n);
        for (int i = 0; i < n; i++) {
            cin >> t[i] >> z[i] >> y[i];
        }
        auto ballonNum = [&t, &z, &y](int i, int time) {
            auto period = t[i] * z[i] + y[i];
            return time / period * z[i] + min((time % period) / t[i], z[i]);
        };
        auto canBlow = [m, n, &ballonNum](int time) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                cnt += ballonNum(i, time);
                if (cnt >= m) {
                    return true;
                }
            }
            return false;
        };
        int lo = -1, hi = m * 200;  // as m might be 0, set lo = -1
        while (lo + 1 < hi) {
            auto mid = lo + (hi - lo) / 2;
            if (canBlow(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        cout << hi << endl;
        auto remaining = m;
        for (int i = 0; i < n; i++) {
            auto num = ballonNum(i, hi);
            if (num > remaining) {
                num = remaining;
            }
            remaining -= num;
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}
