// F. Dense spanning tree
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/F

#include <iostream>
#include <limits>
#include <optional>
#include <tuple>
#include <vector>

class DSU {
   public:
    DSU(size_t n)
        : parent_(n, -1) {
    }
    int Find(int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }
    int Union(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) {
            return -parent_[x];
        }
        if (parent_[x] > parent_[y]) {
            std::swap(x, y);
        }
        parent_[x] += parent_[y];
        parent_[y] = x;
        return -parent_[x];
    }

   private:
    std::vector<int> parent_;
};

using EdgeType = std::tuple<int, int, int>;

std::optional<int> MinimalSpanningTree(const int n, std::vector<EdgeType> &edges) {
    std::sort(edges.begin(), edges.end(), [](const auto &e1, const auto &e2) {
        return std::get<2>(e1) < std::get<2>(e2);
    });

    std::optional<int> res{};
    int min_weight_diff = std::numeric_limits<int>::max();
    int prev_w = std::get<2>(edges[0]) - 1;
    for (auto it_lo = edges.begin(); it_lo != edges.end(); ++it_lo) {
        // no need start from the same weight
        if (prev_w == std::get<2>(*it_lo)) {
            continue;
        }
        prev_w = std::get<2>(*it_lo);
        // try to find a minimum spanning tree
        DSU dsu(n + 1);
        bool can_form = false;
        for (auto it = it_lo; it != edges.end(); ++it) {
            const auto [u, v, w] = *it;
            if (dsu.Find(u) == dsu.Find(v)) {
                continue;
            }
            if (dsu.Union(u, v) >= n) {
                can_form = true;
                const auto weight_diff = w - std::get<2>(*it_lo);
                if (weight_diff < min_weight_diff) {
                    res = min_weight_diff = weight_diff;
                }
                break;
            }
        }
        if (!can_form) {
            break;
        }
    }
    return res;
}

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<EdgeType> edges;
        int from_, to_, weight_;
        while (m--) {
            std::cin >> from_ >> to_ >> weight_;
            edges.emplace_back(from_, to_, weight_);
        }
        const auto res = MinimalSpanningTree(n, edges);
        if (res.has_value()) {
            std::cout << "YES" << '\n'
                      << *res << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
