// D. Cutting a graph
// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/D

#include <algorithm>
#include <iostream>
#include <vector>

class UnionFind {
   public:
    UnionFind(size_t n)
        : parent_(n, -1) {
    }
    int Find(int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }
    void Union(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) {
            return;
        }
        if (parent_[x] > parent_[y]) {
            std::swap(x, y);
        }
        parent_[x] += parent_[y];
        parent_[y] = x;
    }

   private:
    std::vector<int> parent_;
};

std::vector<bool> CutGraph(int n, const std::vector<std::tuple<bool, int, int>> &operations) {
    std::vector<bool> res;
    UnionFind uf(n + 1);
    // note that "After all the operations are applied, the graph contains no edges"
    // so we can handle it reversely as if we were adding edges (i.e. unite vertices)
    for (auto it = operations.rbegin(); it != operations.rend(); ++it) {
        const auto [is_cut, x, y] = *it;
        if (is_cut) {
            uf.Union(x, y);
        } else {
            res.push_back(uf.Find(x) == uf.Find(y));
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}

int main() {
    int n, m, k;
    while (std::cin >> n >> m >> k) {
        int u, v;
        while (m--) {
            std::cin >> u >> v;
        }
        std::vector<std::tuple<bool, int, int>> operations;
        std::string op;
        while (k--) {
            std::cin >> op >> u >> v;
            if (op == "cut") {
                operations.emplace_back(true, u, v);
            } else {
                operations.emplace_back(false, u, v);
            }
        }
        const auto &res = CutGraph(n, operations);
        for (const auto y : res) {
            std::cout << (y ? "YES" : "NO") << std::endl;
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
