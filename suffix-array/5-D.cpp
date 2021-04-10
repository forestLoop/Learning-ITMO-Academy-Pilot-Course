// Borders
// https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/D
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

pair<vector<int>, vector<int>> computeSuffixArray(string s) {
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
    return {pos, class_};
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

long long int countBorders(const vector<int> &lcp) {
    long long int n = lcp.size();
    long long int res = (n + 1) * n / 2;  // empty borders for all substrings
    stack<pair<int, int>> monoStack;      // <pos, elem>
    for (int i = 0; i <= n; i++) {
        int pos = i, elem = (i == n ? 0 : lcp[i]);
        while (!monoStack.empty() && monoStack.top().second >= elem) {
            int lastPos = monoStack.top().first, lastElem = monoStack.top().second;
            monoStack.pop();
            if (lastElem > elem) {
                int threshold = monoStack.empty() ? elem : max(elem, monoStack.top().second);
                long long int posDiff = i - lastPos + 1;
                // border length: threshold + 1, threshold + 2, ..., lastElem
                // lcp index: lastPos, lastPos + 1, ..., i - 1
                res += posDiff * (posDiff - 1) / 2 * (lastElem - threshold);
            }
            pos = lastPos;
        }
        monoStack.push({pos, elem});
    }
    return res;
}

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
    string s;
    while (cin >> s) {
        auto result = computeSuffixArray(s);
        auto lcp = computeLCP(result.first, result.second, s);
        printVector("LCP:", lcp);
        cout << countBorders(lcp) << endl;
    }
    return 0;
}
