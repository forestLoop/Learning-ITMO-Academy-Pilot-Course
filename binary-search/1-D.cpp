// D. Fast search
// https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/D

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        int k;
        cin >> k;
        for (int i = 0; i < k; i++) {
            int l, r;
            cin >> l >> r;
            const auto lo = lower_bound(arr.begin(), arr.end(), l);
            if (lo == arr.end()) {
                cout << 0 << " ";
            } else {
                const auto hi = upper_bound(lo, arr.end(), r);
                cout << hi - lo << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
