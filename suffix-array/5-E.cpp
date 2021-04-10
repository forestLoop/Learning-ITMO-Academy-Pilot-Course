// Refrain
// https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/E
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

pair<long long int, string> findRefrain(const string &s, const vector<int> &lcp, const vector<int> &suffix) {
    stack<int> monoStack;
    const int n = lcp.size();
    long long int maxArea = s.length();
    string res = s;
    for (int i = 0; i <= n; i++) {
        int x = (i == n ? 0 : lcp[i]);
        while (!monoStack.empty() && lcp[monoStack.top()] > x) {
            int tp = monoStack.top();
            monoStack.pop();
            long long int h = lcp[tp], w = (monoStack.empty() ? i : i - 1 - monoStack.top());
            long long int area = h * (w + 1);  // because it's LCP, actually it's `w + 1` substrings
            if (area > maxArea) {
                maxArea = area;
                res = s.substr(suffix[i - w], h);
            }
        }
        monoStack.push(i);
    }
    return {maxArea, res};
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        string s;
        for (auto i = 0; i < n; i++) {
            int d;  // note that 1 <= d <= 10, so using char would lead to WA
            cin >> d;
            s += (d + 'a');
        }
        auto result = computeSuffixArray(s);
        auto lcp = computeLCP(result.first, result.second, s);
        printVector("LCP:", lcp);
        auto refrainResult = findRefrain(s, lcp, result.first);
        cout << refrainResult.first << endl;
        cout << refrainResult.second.length() << endl;
        for (const auto &c : refrainResult.second) {
            int digit = c - 'a';
            cout << digit << " ";
        }
        cout << endl;
    }
    return 0;
}
