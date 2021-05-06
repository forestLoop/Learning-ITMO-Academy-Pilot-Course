// B. Number of Smaller
// https://codeforces.com/edu/course/2/lesson/9/1/practice/contest/307092/problem/B

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
        auto i = 0;
        for (const auto x : b) {
            while (i < n && a[i] < x) {
                i++;
            }
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}
