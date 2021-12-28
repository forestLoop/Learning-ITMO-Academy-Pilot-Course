// G. No refuel
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/G

#include <iostream>
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

int NoRefuel(int n, std::vector<EdgeType> &edges) {
    const auto cmp = [](const EdgeType &e1, const EdgeType &e2) {
        return std::get<2>(e1) > std::get<2>(e2);
    };
    std::priority_queue<EdgeType, std::vector<EdgeType>, decltype(cmp)>
        queue{cmp, edges};
    DSU dsu(n + 1);
    while (!queue.empty()) {
        const auto [u, v, w] = queue.top();
        queue.pop();
        if (dsu.Find(u) == dsu.Find(v)) {
            continue;
        }
        if (dsu.Union(u, v) >= n) {
            return w;
        }
    }
    return -1;
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
        std::cout << NoRefuel(n, edges) << '\n';
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
