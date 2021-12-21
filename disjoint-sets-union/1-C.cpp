// C. Experience
// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C

#include <iostream>
#include <vector>

class Game {
   public:
    Game(size_t n)
        : parent_(n, -1), extra_points_(n, 0) {
    }

    int Find(int x) {
        if (parent_[x] < 0) {
            return x;
        }
        // no path compression
        return Find(parent_[x]);
    }

    void Union(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) {
            return;
        }
        if (std::abs(parent_[x]) < std::abs(parent_[y])) {
            std::swap(x, y);
        }
        // reset extra_points for set y
        extra_points_[y] -= extra_points_[x];
        parent_[x] += parent_[y];
        parent_[y] = x;
    }

    void AddPoints(int x, int points) {
        extra_points_[Find(x)] += points;
    }

    int GetPoints(int x) {
        if (parent_[x] < 0) {
            return extra_points_[x];
        }
        return extra_points_[x] + GetPoints(parent_[x]);
    }

   private:
    std::vector<int> parent_, extra_points_;
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        Game game(n + 1);
        std::string op;
        int x, y, v;
        while (m--) {
            std::cin >> op;
            if (op == "join") {
                std::cin >> x >> y;
                game.Union(x, y);
            } else if (op == "add") {
                std::cin >> x >> v;
                game.AddPoints(x, v);
            } else {
                std::cin >> x;
                std::cout << game.GetPoints(x) << std::endl;
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
