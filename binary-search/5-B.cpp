// B. Multiplication Table
// https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/B

#include <bits/stdc++.h>

using namespace std;

long long findKth(const long long n, const long long k) {
    auto hasLessThanK = [n, k](long long x) {
        long long cnt = 0;
        for (long long i = 1; i <= n; i++) {
            if (x > i) {
                cnt += min((x - 1) / i, n);
                if (cnt >= k) {
                    return false;
                }
            }
        }
        return true;
    };
    long long lo = 1, hi = n * n + 1;
    while (lo + 1 < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (hasLessThanK(mid)) {
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
    long long n, k;
    while (cin >> n >> k) {
        cout << findKth(n, k) << endl;
    }
    return 0;
}
