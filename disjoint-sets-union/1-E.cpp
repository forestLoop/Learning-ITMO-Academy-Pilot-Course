// E. Monkeys
// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/E

#include <iostream>
#include <iterator>
#include <vector>

class Monkeys {
   public:
    Monkeys(size_t n)
        : parent_(n, -1), children_(n) {
        for (size_t i = 0; i < n; ++i) {
            children_[i].push_back(i);
        }
    }
    int Find(int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }
    std::vector<int> Union(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) {
            return {};
        }
        std::vector<int> falling_monkeys;
        if (x > y) {
            std::swap(x, y);
        }
        if (x == 1) {
            falling_monkeys.insert(falling_monkeys.end(), children_[y].begin(), children_[y].end());
        } else {
            children_[x].insert(children_[x].end(), children_[y].begin(), children_[y].end());
        }
        parent_[y] = x;
        return falling_monkeys;
    }

    void Debug() {
        std::cout << "parent_: " << std::endl;
        std::copy(parent_.begin(), parent_.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        std::cout << "children_: " << std::endl;
        for (size_t i = 0; i < children_.size(); ++i) {
            std::cout << i << ": ";
            std::copy(children_[i].begin(), children_[i].end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }

   private:
    std::vector<int> parent_;
    std::vector<std::vector<int>> children_;
};

std::vector<int> ReleaseHands(const std::vector<std::pair<int, int>> &hands, const std::vector<std::pair<int, int>> &actions) {
    const int n = hands.size();
    std::vector<int> res(n, -1);
    // get the final state of all hands
    auto final_hands = hands;
    for (const auto &[monkey, hand_to_release] : actions) {
        if (hand_to_release == 1) {
            final_hands[monkey].first = -1;
        } else {
            final_hands[monkey].second = -1;
        }
    }
    Monkeys monkeys(n);
    for (int i = 0; i < n; ++i) {
        if (final_hands[i].first != -1) {
            monkeys.Union(i, final_hands[i].first);
        }
        if (final_hands[i].second != -1) {
            monkeys.Union(i, final_hands[i].second);
        }
    }
    // monkeys.Debug();
    // now handle all actions reversely
    const int m = actions.size();
    for (auto it = actions.rbegin(); it != actions.rend(); ++it) {
        const auto time = m - 1 - std::distance(actions.rbegin(), it);
        const auto [monkey, hand_to_release] = *it;
        const auto another_monkey = hand_to_release == 1 ? hands[monkey].first : hands[monkey].second;
        for (const auto mk : monkeys.Union(monkey, another_monkey)) {
            res[mk] = time;
        }
        // monkeys.Debug();
    }
    return res;
}

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<std::pair<int, int>> hands(n + 1);
        // add a dummy monkey to simplify the code
        hands[0] = {-1, -1};
        for (int i = 1; i <= n; ++i) {
            std::cin >> hands[i].first >> hands[i].second;
        }
        std::vector<std::pair<int, int>> actions(m);
        for (int i = 0; i < m; ++i) {
            std::cin >> actions[i].first >> actions[i].second;
        }
        const auto &falling_time = ReleaseHands(hands, actions);
        for (auto it = falling_time.begin() + 1; it != falling_time.end(); ++it) {
            std::cout << *it << std::endl;
        }
    }
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
