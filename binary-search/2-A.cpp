// A. Packing Rectangles
// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/A

#include <bits/stdc++.h>

using namespace std;

int main() {
    long long w, h, n;
    while (cin >> w >> h >> n) {
        auto isGood = [w, h, n](long long x) {
            return (x / w) * (x / h) >= n;
        };
        long long lo = 0, hi = max(max(w, h), n * min(h, w));
        while (lo + 1 < hi) {
            auto mid = lo + (hi - lo) / 2;
            if (isGood(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
            // cout << lo << " " << hi << endl;
        }
        cout << hi << endl;
    }
}
