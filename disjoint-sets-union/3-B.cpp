// B. Number of Connected Components on Segments
// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/B

#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stack>
#include <utility>
#include <vector>

class DSU {
   public:
    DSU(size_t n)
        : cnt(2 * n), parent_(n, -1) {
    }

    int Find(int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return Find(parent_[x]);
    }

    void Union(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) {
            return;
        }
        if (parent_[x] > parent_[y]) {
            std::swap(x, y);
        }
        history_.emplace(x, parent_[x]);
        history_.emplace(y, parent_[y]);
        parent_[x] += parent_[y];
        parent_[y] = x;
        cnt -= 2;
    }

    void Persist() {
        history_.emplace(-1, -1);
    }

    void Rollback() {
        while (!history_.empty()) {
            const auto [x, p] = history_.top();
            history_.pop();
            if (x == -1 && p == -1) {
                break;
            }
            parent_[x] = p;
            ++cnt;
        }
    }

    int GetCnt() const {
        return cnt / 2;
    }

   private:
    int cnt;
    std::vector<int> parent_;
    std::stack<std::pair<int, int>> history_;
};

std::vector<int> solve(const int n, const std::vector<std::pair<int, int>> &edges, const std::vector<std::pair<int, int>> &queries) {
    const int m = edges.size(), k = queries.size(), block_size = std::sqrt(m);
    std::vector<int> res(k), queries_idx(k);
    std::iota(queries_idx.begin(), queries_idx.end(), 0);
    std::sort(queries_idx.begin(), queries_idx.end(), [&](int i, int j) -> bool {
        return std::make_pair(queries[i].first / block_size, queries[i].second) < std::make_pair(queries[j].first / block_size, queries[j].second);
    });
    DSU *dsu = nullptr;
    int prev_block = -1, prev_hi = -1;
    for (const auto q_idx : queries_idx) {
        const auto [lo, hi] = queries[q_idx];  // inclusive
        const int lo_block = lo / block_size, hi_block = hi / block_size;
        // re-initialize DSU for each block
        if (lo_block != prev_block) {
            dsu = new DSU(n);
            prev_hi = (lo_block + 1) * block_size - 1;
        }
        prev_block = lo_block;
        if (hi_block == lo_block) {  // within the same block
            dsu->Persist();
            for (int i = lo; i <= hi; ++i) {
                dsu->Union(edges[i].first, edges[i].second);
            }
            res[q_idx] = dsu->GetCnt();
            dsu->Rollback();
        } else {
            // extend from prev_hi to hi
            while (prev_hi < hi) {
                ++prev_hi;
                dsu->Union(edges[prev_hi].first, edges[prev_hi].second);
            }
            // save a checkpoint
            dsu->Persist();
            // handle the leftmost range
            for (int i = lo; i < (lo_block + 1) * block_size; ++i) {
                dsu->Union(edges[i].first, edges[i].second);
            }
            res[q_idx] = dsu->GetCnt();
            // rollback
            dsu->Rollback();
        }
    }
    return res;
}

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<std::pair<int, int>> edges(m);
        int u, v;
        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v;
            edges[i] = {u - 1, v - 1};
        }
        int k;
        std::cin >> k;
        std::vector<std::pair<int, int>> queries(k);
        for (int i = 0; i < k; ++i) {
            std::cin >> u >> v;
            queries[i] = {u - 1, v - 1};
        }
        const auto &res = solve(n, edges, queries);
        std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, "\n"));
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
