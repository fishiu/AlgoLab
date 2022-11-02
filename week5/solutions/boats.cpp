#include <iostream>
#include <algorithm>
#include <vector>

using PI = std::pair<int, int>;
using VPI = std::vector<PI>;

void testcase() {
    int num_boats; std::cin >> num_boats;
    VPI boats;
    for (int i = 0; i < num_boats; ++i) {
        int boat_len, position; std::cin >> boat_len >> position;
        boats.push_back({position, boat_len});
    }
    std::sort(boats.begin(), boats.end());

    VPI ans_boats = {{boats[0].first- boats[0].second, boats[0].first}};
    for (size_t i = 1; i < boats.size(); ++i) {
        auto &last_boat = ans_boats.back();
        int boat_len = boats[i].second;
        int ring_pos = boats[i].first;
        if (ring_pos - boat_len > last_boat.second) {
            ans_boats.push_back({ring_pos - boat_len, ring_pos});
        } else if (ring_pos > last_boat.second) {
            ans_boats.push_back({last_boat.second, last_boat.second + boat_len});
        } else {  // consider replacing
            int possible_start = std::max(last_boat.first, ring_pos - boat_len);
            int possible_end = possible_start + boat_len;
            if (possible_end < last_boat.second) {
                ans_boats.pop_back();
                ans_boats.push_back({possible_start, possible_end});
            }
        }
    }

    std::cout << ans_boats.size() << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t; std::cin >> t;
    while (t--)
        testcase();

    return 0;
}