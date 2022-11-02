#include <iostream>
#include <algorithm>
#include <vector>

using VI = std::vector<int>;


void testcase() {
    int n; std::cin >> n;
    VI tiles(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> tiles[i];
    }

    int sum = 1;
    int len = tiles[0] - 1;

    for (int i = 1; i < n; ++i) {
        // check if no remaining len
        if (len == 0) {
            std::cout << sum << std::endl;
            return;
        }
        sum++;
        len--;

        len = std::max(len, tiles[i] - 1);
    }

    std::cout << sum << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);

    int t; std::cin >> t;  // test cases number
    while (t--)
        testcase();
}