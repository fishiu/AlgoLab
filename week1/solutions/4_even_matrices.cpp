#include <iostream>
#include <vector>


using VI = std::vector<int>;
using VVI = std::vector<VI>;
using VVVI = std::vector<VVI>;


void testcase() {
    int ans = 0;

    int n;
    std::cin >> n;
    VVI mat(n, VI(n, 0));
    VVI sum_row(n, VI(n, 0));  // sum_row[i][j]: sum of [i][0] ~ [i][j - 1]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> mat[i][j];
            if (j == 0)
                sum_row[i][j] = mat[i][j];
            else
                sum_row[i][j] = sum_row[i][j - 1] + mat[i][j];
        }
    }

    VVVI evens(n, VVI(n, VI(n, 0)));
    VVVI odds(n, VVI(n, VI(n, 0)));
    int sum_width;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int width = 0; width <= j; ++width) {
                if (width == j)
                    sum_width = sum_row[i][j];
                else
                    sum_width = sum_row[i][j] - sum_row[i][j - width - 1];

                if (i == 0) {
                    if (sum_width % 2 == 0) {
                        evens[i][j][width] = 1;
                        odds[i][j][width] = 0;
                    } else {
                        evens[i][j][width] = 0;
                        odds[i][j][width] = 1;
                    }
                } else {
                    if (sum_width % 2 == 0) {
                        evens[i][j][width] = evens[i - 1][j][width] + 1;
                        odds[i][j][width] = odds[i - 1][j][width];
                    } else {
                        evens[i][j][width] = odds[i - 1][j][width];
                        odds[i][j][width] = evens[i - 1][j][width] + 1;
                    }
                }

                ans += evens[i][j][width];
            }
        }
    }

    std::cout << ans << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;  // test cases number
    while (t--)
        testcase();
}