// A. Disjoint Sets Union
// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

class UnionFind {
   public:
    UnionFind(size_t n)
        : parent_(n, -1) {
    }
    int Find(const int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }
    void Union(const int x, const int y) {
        auto x_root = Find(x), y_root = Find(y);
        if (x_root == y_root) {
            return;
        }
        if (std::abs(parent_[x_root]) < std::abs(parent_[y_root])) {
            std::swap(x_root, y_root);
        }
        parent_[x_root] += parent_[y_root];
        parent_[y_root] = x_root;
    }

   private:
    std::vector<int> parent_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        UnionFind uf(n + 1);
        std::string op;
        int x, y;
        while (m--) {
            std::cin >> op >> x >> y;
            if (op == "union") {
                uf.Union(x, y);
            } else {
                if (uf.Find(x) == uf.Find(y)) {
                    std::cout << "YES" << std::endl;
                } else {
                    std::cout << "NO" << std::endl;
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
