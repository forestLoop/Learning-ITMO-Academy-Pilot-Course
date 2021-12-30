// I. Bipartite Graph
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/I

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

    void Union(int x, int y) {
        auto [px, lx] = Find(x);
        auto [py, ly] = Find(y);
        if (px == py) {
            return;
        }
        if (parent_[px] > parent_[py]) {
            std::swap(px, py);
            std::swap(lx, ly);
        }
        parent_[px] += parent_[py];
        parent_[py] = px;
        len_[py] = (1 + lx + ly) % 2;
    }

   private:
    std::vector<int> parent_, len_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        DSU dsu(n);
        int shift = 0, op, a, b;
        while (m--) {
            std::cin >> op >> a >> b;
            a = (a + shift) % n, b = (b + shift) % n;
            if (op == 0) {
                dsu.Union(a, b);
            } else {
                const auto [pa, la] = dsu.Find(a);
                const auto [pb, lb] = dsu.Find(b);
                if (la == lb) {
                    std::cout << "YES\n";
                    shift = (shift + 1) % n;
                } else {
                    std::cout << "NO\n";
                }
            }
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
