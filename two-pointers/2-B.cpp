// B. Segment with Big Sum
// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned n;
    unsigned long long s;
    while (cin >> n >> s) {
        vector<unsigned> arr(n);
        for (decltype(n) i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        decltype(n) res = -1, l = 0;
        decltype(s) accSum = 0;
        for (unsigned r = 0; r < n; ++r) {
            accSum += arr[r];
            while (accSum - arr[l] >= s) {
                accSum -= arr[l++];
            }
            if (accSum >= s) {
                res = min(res, r - l + 1);
            }
        }
        if (res > n) {
            cout << -1 << endl;
        } else {
            cout << res << endl;
        }
    }
    return 0;
}
