// B. Parking
// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/B

#include <iostream>
#include <vector>

class ParkingLot {
   public:
    ParkingLot(size_t n)
        : parent_(n, -1) {
    }
    int Find(int x) {
        if (parent_[x] < 0) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }

    int Park(int slot) {
        slot = Find(slot);
        parent_[slot] = (slot + 1) % parent_.size();
        return slot;
    }

   private:
    std::vector<int> parent_;
};

int main() {
    int n;
    while (std::cin >> n) {
        ParkingLot parking(n);
        int slot;
        while (n--) {
            std::cin >> slot;
            std::cout << parking.Park(slot - 1) + 1 << ' ';
        }
        std::cout << std::endl;
    }
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
