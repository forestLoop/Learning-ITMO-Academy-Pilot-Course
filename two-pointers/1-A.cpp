// A. Merging Arrays
// https://codeforces.com/edu/course/2/lesson/9/1/practice/contest/307092/problem/A

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        vector<int> a(n), b(m);
        for (auto i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (auto i = 0; i < m; i++) {
            cin >> b[i];
        }
        auto i = 0, j = 0;
        while (i < n || j < m) {
            if (j == m || i < n && a[i] < b[j]) {
                cout << a[i++] << " ";
            } else {
                cout << b[j++] << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
