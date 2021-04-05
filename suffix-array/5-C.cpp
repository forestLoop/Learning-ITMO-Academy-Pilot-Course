// Sorting Substrings
// https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/C
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

pair<vector<int>, vector<vector<int>>> computeSuffixArray(string s) {
    s += char(32);  // as s can contain any characters with codes from 33 to 127
    int n = s.size();
    vector<int> pos(n), class_(n);
    vector<vector<int>> all_class;
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
    all_class.push_back(class_);
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
        all_class.push_back(class_);
    }
    return {pos, all_class};
}

vector<int> computeLCP(const vector<int> &p, const vector<int> &c,
                       const string &s) {
    int n = p.size();
    int k = 0;
    vector<int> lcp(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int pi = c[i];  // pi >= 1 as "$" is always the smallest suffix string
        int j = p[pi - 1];
        // lcp[pi] = lcp(s[i:], s[j:])
        while (s[i + k] == s[j + k]) {
            k++;
        }
        lcp[pi - 1] = k;  // shift to left by one
        k = max(k - 1, 0);
    }
    return lcp;
}

template <class T>
void printVector(const string &info, const vector<T> &V) {
    cout << info << endl;
    for (const auto &e : V) {
        cout << e << " ";
    }
    cout << endl;
}

void sortSubstrings(vector<pair<int, int>> &pairs, const vector<vector<int>> &all_class) {
    // capture by reference here, otherwise MLE
    // If comp(a,b)==true then comp(b,a)==false
    sort(pairs.begin(), pairs.end(), [&all_class](const pair<int, int> &p1, const pair<int, int> &p2) {
        int l1 = p1.first, r1 = p1.second, len1 = p1.second - p1.first + 1;
        int l2 = p2.first, r2 = p2.second, len2 = p2.second - p2.first + 1;
        int minLen = min(len1, len2);
        int k = 0;
        while ((1 << k) <= minLen) {
            k++;
        }
        k--;
        if (k >= all_class.size()) {  // IMPORTANT as the calculation of all_class might be early terminated
            k = all_class.size() - 1;
        }
        pair<int, int> class1 = {all_class[k][l1 - 1], all_class[k][l1 + minLen - (1 << k) - 1]};
        pair<int, int> class2 = {all_class[k][l2 - 1], all_class[k][l2 + minLen - (1 << k) - 1]};
        bool res = false;
        if (class1 != class2) {
            res = class1 < class2;
        } else {
            if (len1 != len2) {
                res = len1 < len2;
            } else {
                res = p1 < p2;
            }
        }
        return res;
    });
}

int main() {
    string s;
    while (cin >> s) {
        int n;
        cin >> n;
        vector<pair<int, int>> pairs(n);
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            pairs[i] = {l, r};
        }
        auto result = computeSuffixArray(s);
        sortSubstrings(pairs, result.second);
        for (const auto &p : pairs) {
            cout << p.first << " " << p.second << endl;
        }
    }
    return 0;
}
