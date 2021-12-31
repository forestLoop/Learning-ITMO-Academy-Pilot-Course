// C. Dynamic Connectivity Offline
// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/C

#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stack>
#include <tuple>
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

std::vector<int> offline_connectivity(const int n, const std::vector<std::tuple<char, int, int>> &raw_queries) {
    struct Query {
        int u, v;
        int from, to;
    };
    std::vector<std::shared_ptr<Query>> all_queries;
    std::map<int, int> gets;
    std::map<std::pair<int, int>, int> edge_to_idx;
    const int end_time = raw_queries.size();  // by default, all edges end at end_time
    int t = 0;
    for (const auto &[op, u, v] : raw_queries) {
        if (op == '?') {
            gets.emplace(t, -1);
        } else if (op == '+') {
            all_queries.emplace_back(new Query{u, v, t, end_time});
            edge_to_idx[{u, v}] = all_queries.size() - 1;
        } else {
            all_queries[edge_to_idx[{u, v}]]->to = t;
            edge_to_idx.erase({u, v});
        }
        ++t;
    }

    DSU dsu(n);

    const std::function<void(int, int, const std::vector<std::shared_ptr<Query>> &)> handle_range = [&](int lo, int hi, const std::vector<std::shared_ptr<Query>> &queries) {
        // std::cout << "lo=" << lo << ", hi=" << hi << ", queries.size()=" << queries.size() << std::endl;
        dsu.Persist();
        if (lo + 1 == hi) {
            for (const auto &q : queries) {
                if (q->from <= lo && q->to >= hi) {
                    dsu.Union(q->u, q->v);
                }
            }
            if (gets.count(lo) > 0) {
                gets[lo] = dsu.GetCnt();
            }
        } else {
            const int mid = lo + (hi - lo) / 2;
            std::vector<std::shared_ptr<Query>> sub_queries;
            for (const auto &q : queries) {
                if (q->from <= lo && q->to >= hi) {
                    dsu.Union(q->u, q->v);
                } else if (!(q->from >= hi || q->to <= lo)) {
                    sub_queries.emplace_back(q);
                }
            }
            handle_range(lo, mid, sub_queries);
            handle_range(mid, hi, sub_queries);
        }
        dsu.Rollback();
    };

    handle_range(0, t + 1, all_queries);

    std::vector<int> res;
    for (const auto &[k, v] : gets) {
        res.emplace_back(v);
    }
    return res;
}

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        if (m == 0) {
            continue;
        }
        std::vector<std::tuple<char, int, int>> queries;
        char op;
        int u, v;
        queries.reserve(m);
        for (int i = 0; i < m; ++i) {
            std::cin >> op;
            if (op != '?') {
                std::cin >> u >> v;
            }
            queries.emplace_back(op, u - 1, v - 1);
        }
        const auto &res = offline_connectivity(n, queries);
        std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, "\n"));
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
