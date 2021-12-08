// A. Looped Playlist
// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/A

#include <iostream>
#include <numeric>
#include <vector>

// Time: O(N)
// Space: O(1)
std::pair<int, unsigned long long> find_songs_to_listen(const std::vector<int> &songs, unsigned long long threshold) {
    // be careful! you have to static_cast to unsigned long long to avoid overflow
    const unsigned long long sum = std::accumulate(songs.begin(), songs.end(), static_cast<unsigned long long>(0));
    const unsigned long long times = threshold / sum, songs_size = songs.size();
    threshold %= sum;
    if (threshold == 0) {
        return {0, times * songs_size};
    }
    unsigned long long current_cnt = 0, current_sum = 0, best_cnt = -1;
    int best_start = 0;
    for (int current_start = 0; current_start < songs_size; ++current_start) {
        while (current_sum > threshold) {
            current_sum -= songs[(current_start + current_cnt - 1) % songs_size];
            --current_cnt;
        }
        while (current_sum < threshold) {
            current_sum += songs[(current_start + current_cnt) % songs_size];
            ++current_cnt;
        }
        if (current_cnt < best_cnt) {
            best_cnt = current_cnt;
            best_start = current_start;
        }
        // move to the next song
        current_sum -= songs[current_start];
        --current_cnt;
    }
    return {best_start, best_cnt + times * songs_size};
}

int main() {
    int n;
    unsigned long long p;
    while (std::cin >> n >> p) {
        std::vector<int> songs(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> songs[i];
        }
        const auto to_listen = find_songs_to_listen(songs, p);
        // counts from 1 rather than 0, so we need to add 1 to the result
        std::cout << to_listen.first + 1 << " " << to_listen.second << std::endl;
    }
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return nullptr;
}();
