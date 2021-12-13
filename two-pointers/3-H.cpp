// H. A-B Knapsack
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/H

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

// Time: O(NlogN + MlogM)
// Space: O(1)
long long put_into_knapsack(std::vector<int> &a, std::vector<int> &b, const int weight_limit, const int a_weight, const int b_weight) {
    std::sort(a.begin(), a.end(), std::greater<int>());
    std::sort(b.begin(), b.end(), std::greater<int>());
    const int a_size = a.size(), b_size = b.size();
    int b_cnt = std::min(weight_limit / b_weight, b_size);
    // when using `std::accumulate`, always remember to cast `0` correctly
    // otherwise, you may encounter overflow and weird wrong answers
    long long current_weight = b_cnt * b_weight, current_cost = std::accumulate(b.begin(), b.begin() + b_cnt, static_cast<long long>(0));
    long long res = current_cost;
    for (int a_cnt = 1; a_cnt <= a_size; ++a_cnt) {
        current_weight += a_weight;
        current_cost += a[a_cnt - 1];
        while (b_cnt > 0 && current_weight > weight_limit) {
            current_weight -= b_weight;
            current_cost -= b[--b_cnt];
        }
        if (current_weight > weight_limit) {
            break;
        }
        res = std::max(res, current_cost);
    }
    return res;
}

int main() {
    int n, m, s, A, B;
    while (std::cin >> n >> m >> s >> A >> B) {
        std::vector<int> a(n), b(m);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        for (int i = 0; i < m; ++i) {
            std::cin >> b[i];
        }
        std::cout << put_into_knapsack(a, b, s, A, B) << std::endl;
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
