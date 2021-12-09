// E. Knapsack on a Segment
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/E

#include <iostream>
#include <vector>

long long grab(const std::vector<int> &weights, const std::vector<int> &costs, const int weight_limit) {
    const int n = weights.size();
    long long res = 0;
    long long curr_weight = 0, curr_cost = 0;
    int hi = 0;
    for (int lo = 0; lo < n; ++lo) {
        while (hi < n && curr_weight + weights[hi] <= weight_limit) {
            curr_weight += weights[hi];
            curr_cost += costs[hi];
            ++hi;
        }
        res = std::max(res, curr_cost);
        if (hi == n) {  // there's no better solution
            break;
        }
        if (hi > lo) {
            curr_weight -= weights[lo];
            curr_cost -= costs[lo];
        } else {
            // reset `hi` for next iteration
            hi = lo + 1;
        }
    }
    return res;
}

int main() {
    int n, s;
    while (std::cin >> n >> s) {
        std::vector<int> weights(n), costs(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> weights[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> costs[i];
        }
        std::cout << grab(weights, costs, s) << std::endl;
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
