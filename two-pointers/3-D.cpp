// D. Stylish clothes
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/D

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

// Time: O(NlogN)
// Space: O(N)
std::vector<int> choose_clothes(std::vector<std::pair<int, int>> &all_clothes) {
    std::sort(all_clothes.begin(), all_clothes.end());
    const int n = all_clothes.size();
    std::vector<std::queue<int>> window(4);
    int hi = 0, best = 1e5 + 1;
    std::vector<int> result(4);
    for (int lo = 0; lo < n; lo++) {
        while (hi < n && std::any_of(window.begin(), window.end(), [](const auto &q) {
                   return q.empty();
               })) {
            window[all_clothes[hi].second].push(all_clothes[hi].first);
            ++hi;
        }
        if (hi >= n && std::any_of(window.begin(), window.end(), [](const auto &q) {
                return q.empty();
            })) {
            break;
        }
        auto stylish = all_clothes[hi - 1].first - all_clothes[lo].first;
        if (stylish < best) {
            best = stylish;
            for (int i = 0; i < 4; i++) {
                result[i] = window[i].front();
            }
        }
        window[all_clothes[lo].second].pop();
    }
    return result;
}

int main() {
    int n1, n2, n3, n4;
    while (std::cin >> n1) {
        std::vector<std::pair<int, int>> all_clothes;
        all_clothes.resize(n1);
        for (int i = 0; i < n1; i++) {
            std::cin >> all_clothes[i].first;
            all_clothes[i].second = 0;
        }
        std::cin >> n2;
        all_clothes.resize(n1 + n2);
        for (int i = 0; i < n2; i++) {
            std::cin >> all_clothes[n1 + i].first;
            all_clothes[n1 + i].second = 1;
        }
        std::cin >> n3;
        all_clothes.resize(n1 + n2 + n3);
        for (int i = 0; i < n3; i++) {
            std::cin >> all_clothes[n1 + n2 + i].first;
            all_clothes[n1 + n2 + i].second = 2;
        }
        std::cin >> n4;
        all_clothes.resize(n1 + n2 + n3 + n4);
        for (int i = 0; i < n4; i++) {
            std::cin >> all_clothes[n1 + n2 + n3 + i].first;
            all_clothes[n1 + n2 + n3 + i].second = 3;
        }
        const auto &result = choose_clothes(all_clothes);
        for (const auto n : result) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;
    }
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
