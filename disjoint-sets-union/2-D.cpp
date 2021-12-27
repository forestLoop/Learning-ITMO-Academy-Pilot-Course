// D. Bosses
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/D

#include <iostream>
#include <vector>

class Bosses {
   public:
    Bosses(int n)
        : superior_(n, {-1, 0}) {
    }

    void BecomeSubordinate(int subordinate, int boss) {
        superior_[subordinate] = {boss, 1};
    }

    std::pair<int, int> CountSuperiors(int employee) {
        if (superior_[employee].first == -1) {
            return {employee, 0};
        }
        const auto &boss = CountSuperiors(superior_[employee].first);
        superior_[employee].first = boss.first;
        superior_[employee].second += boss.second;
        return superior_[employee];
    }

   private:
    std::vector<std::pair<int, int>>
        superior_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        Bosses bosses(n + 1);
        int q, a, b;
        while (m--) {
            std::cin >> q;
            if (q == 1) {
                std::cin >> a >> b;
                bosses.BecomeSubordinate(a, b);
            } else {
                std::cin >> a;
                std::cout << bosses.CountSuperiors(a).second << '\n';
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
