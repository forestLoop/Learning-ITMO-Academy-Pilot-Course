#include <bits/stdc++.h>

using namespace std;

void countSort(vector<int> &p, vector<int> &c) {
    int n = p.size();
    vector<int> cnt(n);
    for (auto x : c) {
        cnt[x]++;
    }
    vector<int> pos(n);
    pos[0] = 0;
    for (int x = 1; x < n; x++) {
        pos[x] = pos[x - 1] + cnt[x - 1];
    }
    vector<int> p_new(n);
    for (auto x : p) {
        p_new[pos[c[x]]] = x;
        pos[c[x]]++;
    }
    p = p_new;
}

vector<int> computeSuffixArray(string s) {
    s += "$";
    int n = s.size();
    vector<int> pos(n), class_(n);
    // pos[i]: the i-th item's index, i.e., s[pos[i]:] is the i-th item in suffix
    // array
    // class_[i]: the equivalance class of s[i]
    {
        // k = 0
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {s[i], i};
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            pos[i] = a[i].second;
        }
        class_[pos[0]] = 0;
        for (int i = 1; i < n; i++) {
            class_[pos[i]] = class_[pos[i - 1]] + int(a[i - 1].first != a[i].first);
        }
    }
    int k = 0;
    while ((1 << k) < n && class_[pos[n - 1]] < n - 1) {  // for early termination
        // k -> k + 1
        for (int i = 0; i < n; i++) {
            // actually, this is the first counting sort of a radix sort
            //   class_[i] = class_[(pos[i] - (1 << k) + n) % n]
            pos[i] = (pos[i] - (1 << k) + n) % n;
        }
        countSort(pos, class_);
        vector<int> class_new(n);
        class_new[pos[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> prev = {class_[pos[i - 1]],
                                   class_[(pos[i - 1] + (1 << k)) % n]};
            pair<int, int> curr = {class_[pos[i]], class_[(pos[i] + (1 << k)) % n]};
            class_new[pos[i]] = class_new[pos[i - 1]] + int(prev != curr);
        }
        class_ = class_new;
        k++;
    }
    return pos;
}

bool countSubstr(const string &s, const vector<int> &suffix, const string &t) {
    int lo = 0, hi = suffix.size();
    while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        // substr will take care of edge cases when the required sub string extends
        // past the end
        string sub = s.substr(suffix[mid], t.size());
        if (sub == t) {
            return true;
        }
        if (sub < t) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return false;
}

int main() {
    string s;
    while (cin >> s) {
        vector<int> result = computeSuffixArray(s);
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string t;
            cin >> t;
            if (countSubstr(s, result, t)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}
