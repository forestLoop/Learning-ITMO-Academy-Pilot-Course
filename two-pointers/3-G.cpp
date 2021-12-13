// G. Not Very Rude Substring
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/G

#include <iostream>
#include <string>

// Time: O(N)
// Space: O(1)
int find_longest_not_rude(const std::string &s, const long long tolerance) {
    const int n = s.size();
    int res = 0, a_cnt = 0, b_cnt = 0;
    long long rudeness = 0;
    for (int lo = 0, hi = 0; lo < n; ++lo) {
        while (hi < n && rudeness + (s[hi] == 'b' ? a_cnt : 0) <= tolerance) {
            if (s[hi] == 'a') {
                ++a_cnt;
            } else if (s[hi] == 'b') {
                ++b_cnt;
                rudeness += a_cnt;
            }
            ++hi;
        }
        res = std::max(res, hi - lo);
        if (hi >= n) {  // there's no better result
            break;
        }
        if (hi == lo) {
            ++hi;
        } else {
            if (s[lo] == 'a') {
                --a_cnt;
                rudeness -= b_cnt;
            } else if (s[lo] == 'b') {
                --b_cnt;
            }
        }
    }
    return res;
}

int main() {
    long long n, c;
    while (std::cin >> n >> c) {
        std::string s;
        std::cin >> s;
        std::cout << find_longest_not_rude(s, c) << std::endl;
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
