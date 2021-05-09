// F. Segments with Small Spread
// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/F

#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

void add(deque<ull> &minQueue, deque<ull> &maxQueue, const ull elem) {
    while (minQueue.size() > 0 && minQueue.back() > elem) {
        minQueue.pop_back();
    }
    minQueue.push_back(elem);
    while (maxQueue.size() > 0 && maxQueue.back() < elem) {
        maxQueue.pop_back();
    }
    maxQueue.push_back(elem);
}

void remove(deque<ull> &minQueue, deque<ull> &maxQueue, const ull elem) {
    if (minQueue.size() > 0 && minQueue.front() == elem) {
        minQueue.pop_front();
    }
    if (maxQueue.size() > 0 && maxQueue.front() == elem) {
        maxQueue.pop_front();
    }
}

bool good(const deque<ull> &minQueue, const deque<ull> &maxQueue, const ull maxSpread) {
    if (minQueue.size() == 0 || maxQueue.size() == 0) {
        return true;
    }
    return maxQueue.front() - minQueue.front() <= maxSpread;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned n;
    unsigned long long k;
    while (cin >> n >> k) {
        vector<unsigned long long> arr(n);
        for (decltype(n) i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        decltype(n) l = 0;
        decltype(k) res = 0;
        deque<ull> minQueue{}, maxQueue{};
        for (decltype(n) r = 0; r < n; ++r) {
            add(minQueue, maxQueue, arr[r]);
            while (!good(minQueue, maxQueue, k)) {
                remove(minQueue, maxQueue, arr[l++]);
            }
            res += (r - l + 1);
        }
        cout << res << endl;
    }
    return 0;
}
