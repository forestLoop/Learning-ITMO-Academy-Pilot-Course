// C. Very Easy Task
// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/C

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, x, y;
    while (cin >> n >> x >> y) {
        auto canCopy = [n, x, y](int t) {
            int cnt = 0;
            if (t < min(x, y)) {
                cnt = 0;
            } else {
                cnt = 1 + (t - min(x, y)) / x + (t - min(x, y)) / y;
            }
            return cnt >= n;
        };
        int lo = 0, hi = n * min(x, y);
        while (lo + 1 < hi) {
            auto mid = lo + (hi - lo) / 2;
            if (canCopy(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        cout << hi << endl;
    }
    return 0;
}
