// F.String Game
// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/F

#include <bits/stdc++.h>

using namespace std;

template <class T>
void printVector(const string &info, const vector<T> &V) {
#ifndef ONLINE_JUDGE
    cout << info << endl;
    for (const auto &e : V) {
        cout << e << " ";
    }
    cout << endl;
#endif
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string p, t;
    while (cin >> p >> t) {
        const int n = p.size();
        vector<int> deletion(n);
        for (auto i = 0; i < n; i++) {
            cin >> deletion[i];
        }
        auto good = [n, &p, &t, &deletion](int cnt) {
            string pNew(p);
            for (auto i = 0; i < cnt; i++) {
                pNew[deletion[i] - 1] = '*';
            }
            int cursor = 0;
            for (const auto &c : t) {
                while (cursor < n && pNew[cursor] != c) {
                    cursor++;
                }
                if (cursor >= n) {
                    return false;
                }
                cursor++;
            }
            return true;
        };
        int lo = 0, hi = n - t.size() + 1;
        while (lo + 1 < hi) {
            auto mid = lo + (hi - lo) / 2;
            if (good(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        cout << lo << endl;
    }
    return 0;
}
