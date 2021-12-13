// F. Card Substrings
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/F

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Time: O(N)
// Space: O(1)
long long count_substrings(const std::string &str, const std::string &cards) {
    std::vector<int> cards_cnt(26, 0);
    for (const auto &c : cards) {
        ++cards_cnt[c - 'a'];
    }
    long long res = 0;
    const int n = str.size();
    for (int lo = 0, hi = 0; lo < n; ++lo) {
        while (hi < n && cards_cnt[str[hi] - 'a'] > 0) {
            --cards_cnt[str[hi++] - 'a'];
        }
        res += hi - lo;
        if (lo != hi) {
            ++cards_cnt[str[lo] - 'a'];
        } else {
            hi = lo + 1;
        }
    }
    return res;
}

int main() {
    int m, n;
    while (std::cin >> n >> m) {
        std::string str, cards;
        std::cin >> str >> cards;
        std::cout << count_substrings(str, cards) << std::endl;
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
