#include <iostream>
#include <algorithm>


void testcase() {
    int n; std::cin >> n;
    int result = 0, curr_even_cnt = 0, curr_odd_cnt = 0;

    for (int i = 0; i < n; ++i) {
        int x = 0; std::cin >> x;
        if (x % 2 == 0) {
            curr_even_cnt++;  // include itself
            result += curr_even_cnt;
        } else {
            std::swap(curr_even_cnt, curr_odd_cnt);
            curr_odd_cnt++;  // include itself
            result += curr_even_cnt;
        }
    }

    std::cout << result << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;  // test cases number
    while (t--)
        testcase();
}
