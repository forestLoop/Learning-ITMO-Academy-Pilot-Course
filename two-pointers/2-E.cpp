// E. Segments with Small Set
// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/E

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned n, k;
    while (cin >> n >> k) {
        vector<unsigned> arr(n);
        for (decltype(n) i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        decltype(n) l = 0;
        unsigned long long res = 0;
        unordered_map<unsigned, unsigned> cnt{};
        for (decltype(n) r = 0; r < n; ++r) {
            ++cnt[arr[r]];
            while (cnt.size() > k) {
                --cnt[arr[l]];
                if (cnt[arr[l]] == 0) {
                    cnt.erase(arr[l]);
                }
                ++l;
            }
            // cout << l << " " << r << endl;
            res += (r - l + 1);
        }
        cout << res << endl;
    }
    return 0;
}
