#include <bits/stdc++.h>

using namespace std;

vector<int> computeSuffixArray(string s) {
    s += "$";
    int n = s.size();
    vector<int> p(n), c(n);
    {
        // k = 0
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {s[i], i};
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + int(a[i - 1].first != a[i].first);
        }
    }
    int k = 0;
    while ((1 << k) < n && c[p[n - 1]] < n - 1) {  // for early termination
        // k -> k + 1
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + int(a[i - 1].first != a[i].first);
        }
        k++;
    }
    return p;
}

int main() {
    string s;
    while (cin >> s) {
        vector<int> result = computeSuffixArray(s);
        for (auto it = result.begin(); it != result.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
    return 0;
}
