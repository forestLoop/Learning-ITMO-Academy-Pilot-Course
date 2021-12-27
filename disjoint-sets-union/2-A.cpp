// A. People are leaving
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/A

#include <iostream>
#include <numeric>
#include <vector>

// Union Find
// Time: O(m)
// Space: O(n)

class People {
   public:
    People(size_t n)
        : parent_(n, -1), max_(n) {
        std::iota(max_.begin(), max_.end(), 0);
    }

    int FindRight(int x) {
        return max_[Find(x)];
    }

    void Leave(int x) {
        Union(x, x + 1);
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
        max_[x] = std::max(max_[x], max_[y]);
    }

   private:
    std::vector<int> parent_, max_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        People row(n + 2);
        char op;
        int x, y;
        while (m--) {
            std::cin >> op >> x;
            if (op == '-') {
                row.Leave(x);
            } else {
                y = row.FindRight(x);
                // don't use std::endl, otherwise you will get TLE
                std::cout << (y == n + 1 ? -1 : y) << '\n';
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
