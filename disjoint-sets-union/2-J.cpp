// J. First Non-Bipartite Edge
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/J

#include <iostream>
#include <utility>
#include <vector>

class DSU {
   public:
    DSU(size_t n)
        : parent_(n, -1), len_(n, 0) {
    }

    std::pair<int, int> Find(int x) {
        if (parent_[x] < 0) {
            return {x, 0};
        }
        const auto [p, l] = Find(parent_[x]);
        parent_[x] = p;
        len_[x] = (len_[x] + l) % 2;
        return {p, len_[x]};
    }

    bool Union(int x, int y) {
        auto [px, lx] = Find(x);
        auto [py, ly] = Find(y);
        if (px == py) {
            return lx != ly;
        }
        if (parent_[px] > parent_[py]) {
            std::swap(px, py);
            std::swap(lx, ly);
        }
        parent_[px] += parent_[py];
        parent_[py] = px;
        len_[py] = (1 + lx + ly) % 2;
        return true;
    }

   private:
    std::vector<int> parent_, len_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        DSU dsu(n);
        int a, b;
        bool bipartite = true;
        for (int i = 1; i <= m; ++i) {
            std::cin >> a >> b;
            if (bipartite && !dsu.Union(a - 1, b - 1)) {
                std::cout << i << std::endl;
                bipartite = false;
            }
        }
        if (bipartite) {
            std::cout << -1 << std::endl;
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
