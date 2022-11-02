/**
 * max points, min distance
 * coord
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using VI = std::vector<int>;
using SI = std::set<int>;

void insert_result(int left_coord, int right_coord, SI &result) {
    if ((right_coord - left_coord) % 2 == 0) {
        result.insert((right_coord + left_coord) / 2);
    } else {
        double mid = (right_coord + left_coord) / 2.0;
        result.insert((int) (mid - 0.5));
        result.insert((int) (mid + 0.5));
    }
}


void testcase() {
    int n; std::cin >> n;
    VI parasols(n);
    int max_num = 0, min_dist = INT32_MAX;
    SI results;

    for (int i = 0; i < n; ++i)
        std::cin >> parasols[i];

    std::sort(parasols.begin(), parasols.end());

    int left_idx = -1, right_idx = 0;
    int left_coord, right_coord;
    int debug_cnt = 0;
    while (right_idx < n - 1) {
        left_idx ++;
        left_coord = parasols[left_idx];
        right_coord = left_coord + 200;
        // find the first one out of the range
        auto right_iter = std::upper_bound(parasols.begin(), parasols.end(), right_coord);
        if (right_iter == parasols.end()) { // all points are in the range, we can end search
            right_idx = n - 1;
        } else {
            right_idx = (int) (right_iter - parasols.begin()) - 1;
        }
        right_coord = parasols[right_idx];
        // comparing stuff
        int num = right_idx - left_idx + 1;
        int dist = (right_coord - left_coord + 1) / 2;
        if (num > max_num) {
            max_num = num;
            min_dist = dist;
            results.clear();
            insert_result(left_coord, right_coord, results);
        } else if (num == max_num) {
            if (dist < min_dist) {
                min_dist = dist;
                results.clear();
                insert_result(left_coord, right_coord, results);
            } else if (dist == min_dist) {
                insert_result(left_coord, right_coord, results);
            }
        }
        debug_cnt ++;
    }

    std::cout << max_num << " " << min_dist << std::endl;
    for (const auto &item: results) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t; std::cin >> t;
    while (t--)
        testcase();

    return 0;
}