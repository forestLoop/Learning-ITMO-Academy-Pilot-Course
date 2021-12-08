// B. Total Length
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/B

#include <algorithm>
#include <iostream>
#include <vector>

long long calc_length(const std::vector<int> &arr, const long long s) {
    const int n = arr.size();
    long long res = 0, curr_sum = 0;
    int hi = 0;
    for (int lo = 0; lo < n; ++lo) {
        // it's impossible to have any segment starting from `lo`
        if (arr[lo] > s) {
            continue;
        }
        // reset `hi` if we skipped too many elements
        if (hi <= lo) {
            hi = lo + 1;
            curr_sum = arr[lo];
        }
        // extend the segment as long as possible
        while (hi < n && curr_sum + arr[hi] <= s) {
            curr_sum += arr[hi];
            ++hi;
        }
        res += static_cast<long long>(hi - lo) * (hi - lo + 1) / 2;
        // remove the first element of the segment for the next iteration
        curr_sum -= arr[lo];
    }
    return res;
}

int main() {
    int n;
    long long s;
    while (std::cin >> n >> s) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
        }
        std::cout << calc_length(arr, s) << std::endl;
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return nullptr;
}();
