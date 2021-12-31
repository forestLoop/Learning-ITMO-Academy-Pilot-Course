// A. DSU with rollback
// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/A

#include <iostream>
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

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        DSU dsu(n);
        std::string op;
        int a, b;
        while (m--) {
            std::cin >> op;
            if (op == "persist") {
                dsu.Persist();
            } else if (op == "rollback") {
                dsu.Rollback();
                std::cout << dsu.GetCnt() << '\n';
            } else {
                std::cin >> a >> b;
                dsu.Union(a - 1, b - 1);
                std::cout << dsu.GetCnt() << '\n';
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
