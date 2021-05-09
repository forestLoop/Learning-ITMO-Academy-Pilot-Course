// G. Coprimer Segment
// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/G

#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

template <class T>
class GCDStack {
   private:
    stack<T> s{}, gcdStack{};

   public:
    GCDStack() {
        gcdStack.push(0);
    }

    void push(T elem) {
        s.push(elem);
        gcdStack.push(__gcd(elem, gcdStack.top()));
    }
    T pop() {
        auto res = s.top();
        gcdStack.pop();
        s.pop();
        return res;
    }
    T gcd() const {
        return gcdStack.top();
    }
    decltype(s.size()) size() const {
        return s.size();
    }
};

void add(GCDStack<ull> &gs1, GCDStack<ull> &gs2, const ull elem) {
    gs2.push(elem);
}

ull remove(GCDStack<ull> &gs1, GCDStack<ull> &gs2) {
    if (gs1.size() == 0) {
        while (gs2.size() > 0) {
            gs1.push(gs2.pop());
        }
    }
    return gs1.pop();
}

bool good(const GCDStack<ull> &gs1, const GCDStack<ull> &gs2) {
    return __gcd(gs1.gcd(), gs2.gcd()) == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned n;
    while (cin >> n) {
        vector<ull> arr(n);
        for (decltype(n) i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        decltype(n) res = -1, l = 0;
        GCDStack<ull> gs1, gs2;
        for (unsigned r = 0; r < n; ++r) {
            add(gs1, gs2, arr[r]);
            while (good(gs1, gs2)) {
                res = min(res, r - l + 1);
                remove(gs1, gs2);
                ++l;
            }
        }
        if (res > n) {
            cout << -1 << endl;
        } else {
            cout << res << endl;
        }
    }
    return 0;
}
