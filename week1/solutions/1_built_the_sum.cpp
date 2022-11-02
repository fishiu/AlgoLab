#include <iostream>

int main() {
    int t; std::cin >> t;  // test cases number
    while (t--) {
        int n; std::cin >> n;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int x; std::cin >> x;
            sum += x;
        }
        std::cout << sum << std::endl;
    }
}