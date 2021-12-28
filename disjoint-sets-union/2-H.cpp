// H. Oil business
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/H

#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>

using EdgeType = std::tuple<int, int, int>;

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

std::vector<int> DeleteAMAP(const int n, const long long max_delete_costs, const std::vector<EdgeType> &edges) {
    std::vector<int> indices(edges.size());
    // sort by costs (descending)
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&edges](int i, int j) {
        return std::get<2>(edges[i]) > std::get<2>(edges[j]);
    });

    const long long total_costs = std::accumulate(edges.begin(), edges.end(), static_cast<long long>(0), [](long long acc, const EdgeType &e) {
        return acc + std::get<2>(e);
    });
    long long min_keep_costs = total_costs - max_delete_costs;

    std::vector<int> to_keep;
    std::queue<int> to_delete;
    DSU dsu(n + 1);

    auto idx_it = indices.begin();
    for (; idx_it != indices.end(); ++idx_it) {
        const auto idx = *idx_it;
        const auto [u, v, w] = edges[idx];
        if (dsu.Find(u) == dsu.Find(v)) {
            to_delete.push(idx);
            continue;
        }
        to_keep.push_back(idx);
        min_keep_costs -= w;
        if (dsu.Union(u, v) >= n) {
            ++idx_it;
            break;
        }
    }

    while (min_keep_costs > 0) {
        if (!to_delete.empty()) {
            const auto idx = to_delete.front();
            to_delete.pop();
            min_keep_costs -= std::get<2>(edges[idx]);
        } else {
            const auto idx = *idx_it;
            ++idx_it;
            min_keep_costs -= std::get<2>(edges[idx]);
        }
    }

    std::vector<int> really_to_delete;
    really_to_delete.reserve(to_delete.size() + (indices.end() - idx_it));
    while (!to_delete.empty()) {
        really_to_delete.push_back(to_delete.front() + 1);
        to_delete.pop();
    }
    for (; idx_it != indices.end(); ++idx_it) {
        really_to_delete.push_back(*idx_it + 1);
    }
    return really_to_delete;
}

int main() {
    int n, m;
    long long s;
    while (std::cin >> n >> m >> s) {
        std::vector<EdgeType> edges;
        int from_, to_, weight_;
        while (m--) {
            std::cin >> from_ >> to_ >> weight_;
            edges.emplace_back(from_, to_, weight_);
        }
        const auto &res = DeleteAMAP(n, s, edges);
        std::cout << res.size() << '\n';
        std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
