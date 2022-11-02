#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using VI = std::vector<int>;

void testcase() {
    int num_friends, num_boxes;
    std::cin >> num_friends >> num_boxes;
    VI friends(num_friends);
    VI boxes(num_boxes);
    for (int i = 0; i < num_friends; ++i)
        std::cin >> friends[i];
    for (int i = 0; i < num_boxes; ++i)
        std::cin >> boxes[i];

    std::sort(friends.begin(), friends.end(), std::greater<>());
    std::sort(boxes.begin(), boxes.end(), std::greater<>());

    if (friends[0] < boxes[0]) {
        std::cout << "impossible" << std::endl;
        return;
    }

    // binary search for ans
    long mid = -1, lo = std::ceil((double) num_boxes / num_friends), hi = num_boxes;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        // test if mid works
        bool works = true;
        for (int i = 0; i < num_friends; ++i) {
            long first_box_idx = i * mid;
            if (first_box_idx < num_boxes && boxes[first_box_idx] > friends[i]) {
                // the most heavy box for this friend
                works = false;
                break;
            }  // else: this friend has no effect on result
        }
        if (works)  // if mid works
            hi = mid;
        else
            lo = mid + 1;
    }

    std::cout << 3 * lo - 1 << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}