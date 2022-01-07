// C. Number of Minimums on a Segment
// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

#include <functional>
#include <iostream>
#include <limits>
#include <vector>

template <typename ElementType>
class SegmentTree {
   public:
    SegmentTree(size_t n, const ElementType &nil, const std::function<ElementType(const ElementType &, const ElementType &)> &merge)
        : n_(n), nil_(nil), merge_(merge), tree_(2 * n, nil) {
    }

    void Build(std::vector<ElementType> &&arr) {
        if (arr.size() > n_) {
            throw std::runtime_error("Invalid input array size");
        }
        for (size_t i = 0; i < n_; ++i) {
            tree_[i + n_] = std::move(arr[i]);
        }
        for (size_t i = n_ - 1; i > 0; --i) {
            tree_[i] = merge_(tree_[2 * i], tree_[2 * i + 1]);
        }
    }

    void Set(size_t i, const ElementType &x) {
        if (i >= n_) {
            throw std::runtime_error("Invalid index");
        }
        tree_[i + n_] = x;
        for (i += n_; i > 1; i >>= 1) {
            tree_[i >> 1] = merge_(tree_[i], tree_[i ^ 1]);
        }
    }

    ElementType Query(size_t l, size_t r) {
        if (l > r || l >= n_ || r > n_) {
            throw std::runtime_error("Invalid range");
        }
        ElementType res = nil_;
        for (l += n_, r += n_; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = merge_(res, tree_[l++]);
            }
            if (r & 1) {
                res = merge_(res, tree_[--r]);
            }
        }
        return res;
    }

   private:
    const size_t n_;
    const ElementType nil_;
    const std::function<ElementType(const ElementType &, const ElementType &)> merge_;
    std::vector<ElementType> tree_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        using Elem = std::pair<int, int>;
        SegmentTree<Elem> min_count_tree(n, {std::numeric_limits<int>::max(), 1}, [](const Elem &a, const Elem &b) -> Elem {
            if (a.first < b.first) {
                return a;
            } else if (a.first > b.first) {
                return b;
            } else {
                return {a.first, a.second + b.second};
            }
        });
        std::vector<Elem> arr(n, {0, 1});
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i].first;
        }
        min_count_tree.Build(std::move(arr));
        while (m--) {
            int op;
            std::cin >> op;
            if (op == 1) {
                int i, x;
                std::cin >> i >> x;
                min_count_tree.Set(i, {x, 1});
            } else {
                int l, r;
                std::cin >> l >> r;
                const auto &res = min_count_tree.Query(l, r);
                std::cout << res.first << " " << res.second << "\n";
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
