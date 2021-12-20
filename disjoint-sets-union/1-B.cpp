// B. Disjoint Sets Union 2
// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/B

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

class UnionFindMinMax {
   public:
    UnionFindMinMax(size_t n)
        : parent_(n, -1), min_(n), max_(n) {
        std::iota(min_.begin(), min_.end(), 0);
        std::iota(max_.begin(), max_.end(), 0);
    }
    int Find(const int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }
    std::tuple<int, int, int> Get(const int x) {
        const auto x_root = Find(x);
        return {
            min_[x_root],
            max_[x_root],
            -parent_[x_root]};
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
        min_[x_root] = std::min(min_[x_root], min_[y_root]);
        max_[x_root] = std::max(max_[x_root], max_[y_root]);
        parent_[y_root] = x_root;
    }

   private:
    std::vector<int> parent_, min_, max_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        UnionFindMinMax uf(n + 1);
        std::string op;
        int x, y;
        while (m--) {
            std::cin >> op;
            if (op == "union") {
                std::cin >> x >> y;
                uf.Union(x, y);
            } else {
                std::cin >> x;
                const auto &res = uf.Get(x);
                std::cout << std::get<0>(res) << " " << std::get<1>(res) << " " << std::get<2>(res) << std::endl;
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
