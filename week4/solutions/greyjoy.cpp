#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using VI = std::vector<int>;
using VVI = std::vector<VI>;
using PI = std::pair<int, int>;  // score, waterway_id

struct cmp {
    bool operator()(const PI &a, const PI &b) {
        return a.first < b.first;
    }
};

using PQ = std::priority_queue<PI, std::vector<PI>, cmp>;
using VPQ = std::vector<PQ>;

void testcase() {
    int num_islands, num_men, num_waterway;
    std::cin >> num_islands >> num_men >> num_waterway;

    VI conquer;
    for (int i = 0; i < num_islands; ++i) {
        int conq;
        std::cin >> conq;
        conquer.push_back(conq);
    }

    VVI waterway(num_waterway, VI());
    for (int i = 0; i < num_waterway; ++i) {
        int waterway_len;
        std::cin >> waterway_len;
        for (int j = 0; j < waterway_len; ++j) {
            int island_idx;
            std::cin >> island_idx;
            if (island_idx == 0) {
                // assert(j == 0);
                continue;
            }
            waterway[i].push_back(conquer[island_idx]);
        }
    }

    // if pyke is conquered
    int remained_men = num_men - conquer[0];
    VPQ man2islands(remained_men + 1, PQ());
    for (int i = 0; i < num_waterway; ++i) {
        int used_men = 0;
        for (size_t j = 0; j < waterway[i].size(); ++j) {
            used_men += waterway[i][j];
            if (used_men > remained_men) break;  // this plan will never come true

            int score = (int) j + 1;  // take j + 1 islands
            man2islands[used_men].push({score, i});
        }
    }

    int max_islands = -1;
    int ans;
    for (size_t used_men = 1; used_men < man2islands.size(); ++used_men) {
        auto &islands_queue = man2islands[used_men];
        if (islands_queue.empty()) continue;

        int score = islands_queue.top().first;
        int waterway_id = islands_queue.top().second;

        int another_used_men = (int) (remained_men - used_men);
        if (another_used_men == 0) {  // no need to find another part
            max_islands = std::max(max_islands, score);
            continue;
        }

        auto &another_islands_queue = man2islands[another_used_men];
        if (another_islands_queue.empty()) continue;

        if (another_islands_queue.top().second == waterway_id) {  // repeat situation
            if (another_islands_queue.size() <= 1) continue;  // no way
            another_islands_queue.pop();  // get second best
        }
        int another_score = another_islands_queue.top().first;

        max_islands = std::max(max_islands, score + another_score);
    }
    ans = max_islands == -1 ? 0 : max_islands + 1;

    std::cout << ans << std::endl;  // don't forget pyke
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}