// B. Splitting an Array
// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/B

#include <bits/stdc++.h>

using namespace std;

long long findMinSum(const vector<int> &a, int k) {
    auto n = a.size();
    auto canSplit = [&a, k, n](long long sum) {
        int cnt = 1;
        long long tempSum = 0;
        for (const auto x : a) {
            if (tempSum + x > sum) {
                cnt++;
                tempSum = 0;
            }
            if (x > sum || cnt > k) {
                return false;
            }
            tempSum += x;
        }
        return true;
    };

    long long lo = 0, hi = n * 1e9;
    while (lo + 1 < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (canSplit(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return hi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n);
        for (auto i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << findMinSum(a, k) << endl;
    }
    return 0;
}
