// C. Che city
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/C

#include <iostream>
#include <vector>

// Time: O(N)
// Space: O(1)
long long organize_dates(const std::vector<int> &monuments, const int radius) {
    const int n = monuments.size();
    long long res = 0;
    int right = 0;
    for (int left = 0; left < n; ++left) {
        while (right < n && monuments[right] - monuments[left] <= radius) {
            ++right;
        }
        // there's no need to further check
        if (right >= n) {
            break;
        }
        res += (n - right);
    }
    return res;
}

int main() {
    int n, r;
    while (std::cin >> n >> r) {
        std::vector<int> monuments(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> monuments[i];
        }
        std::cout << organize_dates(monuments, r) << std::endl;
    }
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
