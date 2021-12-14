// I. Segment with the Required Subset
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/I

#include <bitset>
#include <iostream>
#include <stack>
#include <vector>

constexpr int MAX_SUM = 1000;
constexpr int BITSET_SIZE = MAX_SUM + 1;

class KnapsackStack {
   public:
    KnapsackStack() {
        bitsets_.push(1);
    }
    void Push(int value) {
        values_.push(value);
        const auto &last = bitsets_.top();
        bitsets_.push(last | last << value);
    }
    int TopVal() const {
        return values_.top();
    }
    std::bitset<BITSET_SIZE> TopBitset() const {
        return bitsets_.top();
    }
    void Pop() {
        bitsets_.pop();
        values_.pop();
    }
    bool Empty() const {
        return values_.empty();
    }

   private:
    std::stack<int> values_{};
    std::stack<std::bitset<BITSET_SIZE>> bitsets_{};
};

bool good(KnapsackStack &stack, KnapsackStack &stack_rev, const int expected_sum) {
    const auto &bits1 = stack.TopBitset(), &bits2 = stack_rev.TopBitset();
    for (int i = 0; i <= expected_sum; ++i) {
        if (bits1[i] && bits2[expected_sum - i]) {
            return true;
        }
    }
    return false;
}

void add(KnapsackStack &stack, const int value) {
    stack.Push(value);
}

void remove(KnapsackStack &stack, KnapsackStack &stack_rev) {
    if (stack_rev.Empty()) {
        while (!stack.Empty()) {
            stack_rev.Push(stack.TopVal());
            stack.Pop();
        }
    }
    stack_rev.Pop();
}

// Time: O(NS)
// Space: O(N)
int min_good_segment(const std::vector<int> &arr, const int expected_sum) {
    KnapsackStack stack, stack_rev;
    const int n = arr.size();
    int res = n + 1;
    for (int lo = 0, hi = 0; lo < n; ++lo) {
        while (hi < n && !good(stack, stack_rev, expected_sum)) {
            add(stack, arr[hi++]);
        }
        if (hi >= n && !good(stack, stack_rev, expected_sum)) {
            break;
        }
        // hi > lo must hold as expected_sum != 0
        res = std::min(res, hi - lo);
        remove(stack, stack_rev);
    }
    return (res > n) ? -1 : res;
}

int main() {
    int n, s;
    while (std::cin >> n >> s) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        std::cout << min_good_segment(arr, s) << std::endl;
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
