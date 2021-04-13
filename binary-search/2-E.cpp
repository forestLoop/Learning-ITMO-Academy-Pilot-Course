// E. Equation
// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/E

#include <bits/stdc++.h>

using namespace std;

int main() {
    double C;
    while (cin >> C) {
        auto greater = [C](double guess) {
            auto x = guess * guess;
            return x * x + guess >= C;
        };
        double lo = 0.5, hi = C;
        const int iterations = 100;
        for (auto i = 0; i < iterations; i++) {
            auto mid = lo + (hi - lo) / 2;
            if (greater(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        cout << setprecision(20) << lo * lo << endl;
    }
    return 0;
}
