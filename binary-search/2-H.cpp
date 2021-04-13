// G. Student Councils
// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/H

#include <bits/stdc++.h>

using namespace std;

int main() {
    string recipe;
    while (cin >> recipe) {
        int B = 0, S = 0, C = 0;
        for (const auto &x : recipe) {
            if (x == 'B') {
                B++;
            } else if (x == 'S') {
                S++;
            } else {
                C++;
            }
        }
        int nb, ns, nc, pb, ps, pc;
        cin >> nb >> ns >> nc >> pb >> ps >> pc;
        long long rubles;
        cin >> rubles;
        auto canMake = [B, S, C, nb, ns, nc, pb, ps, pc, rubles](long long cnt) {
            auto BB = max(B * cnt - nb, 0ll) * pb;
            auto CC = max(C * cnt - nc, 0ll) * pc;
            auto SS = max(S * cnt - ns, 0ll) * ps;
            return BB + CC + SS <= rubles;
        };
        long long lo = -1, hi = rubles + nb + ns + nc + 1;
        while (lo + 1 < hi) {
            auto mid = lo + (hi - lo) / 2;
            if (canMake(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        cout << lo << endl;
    }
    return 0;
}
