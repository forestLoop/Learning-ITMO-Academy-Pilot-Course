// C. Restructuring Company
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/C

#include <iostream>
#include <set>
#include <vector>

class Company {
   public:
    Company(int n)
        : parent_(n, -1) {
        std::set<int>::iterator it = unconnected_.end();
        for (int i = 0; i < n; ++i) {
            it = unconnected_.insert(it, i);
        }
    }

    int Find(int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }

    int UnionTwo(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) {
            return x;
        }
        if (parent_[x] > parent_[y]) {
            std::swap(x, y);
        }
        parent_[x] += parent_[y];
        parent_[y] = x;
        return x;
    }

    void UnionRange(int x, int y) {
        int pos = x;
        while ((pos = *unconnected_.lower_bound(pos)) < y) {
            unconnected_.erase(pos);
            UnionTwo(pos, pos + 1);
        }
    }

   private:
    std::vector<int> parent_;
    std::set<int> unconnected_;
};

int main() {
    int n, q;
    while (std::cin >> n >> q) {
        Company company(n + 1);
        int op_type, x, y;
        while (q--) {
            std::cin >> op_type >> x >> y;
            if (op_type == 1) {
                company.UnionTwo(x, y);
            } else if (op_type == 2) {
                company.UnionRange(x, y);
            } else {
                std::cout << (company.Find(x) == company.Find(y) ? "YES" : "NO") << '\n';
            }
        }
    }
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
