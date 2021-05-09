// A. Segment with Small Sum
// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/A

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
        decltype(n) res = 0, l = 0;
        decltype(s) accSum = 0;
        for (unsigned r = 0; r < n; ++r) {
            accSum += arr[r];
            while (accSum > s) {
                accSum -= arr[l++];
            }
            res = max(res, r - l + 1);
        }
        cout << res << endl;
    }
    return 0;
}
