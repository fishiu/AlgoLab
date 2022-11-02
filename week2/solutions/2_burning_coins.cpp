#include <iostream>
#include <algorithm>
#include <vector>


using VI = std::vector<int>;
using PBI = std::pair<bool, int>;  // bool: is left, int: sum
using VVP = std::vector<std::vector<PBI>>;

VVP memo;


PBI max_value(VI &coins, int start, int end) {
    if (memo[start][end].second != -1) {
        return memo[start][end];
    }

    if (start == end) {  // only one
        return std::make_pair(true, coins[start]);
    }

    if (start + 1 == end) {  // two: big one
        if (coins[start] > coins[end]) {
            memo[start][end] = std::make_pair(true, coins[start]);
            return memo[start][end];
        } else {
            memo[start][end] = std::make_pair(false, coins[end]);
            return memo[start][end];
        }
    }

    if (start + 2 == end) {  // three: big two
        if (coins[start] > coins[end]) {
            PBI oppose = max_value(coins, start + 1, end);
            if (oppose.first) {  // take left
                memo[start][end] = std::make_pair(true, coins[start] + coins[end]);
                return memo[start][end];
            } else {
                memo[start][end] = std::make_pair(true, coins[start] + coins[start + 1]);
                return memo[start][end];
            }
        } else {
            PBI oppose = max_value(coins, start, end - 1);
            if (oppose.first) {  // take left
                memo[start][end] = std::make_pair(false, coins[end] + coins[end - 1]);
                return memo[start][end];
            } else {
                memo[start][end] = std::make_pair(false, coins[end] + coins[start]);
                return memo[start][end];
            }
        }
    }

    // more than three
    PBI if_left = max_value(coins, start + 1, end);
    int left_sum = coins[start];
    if (if_left.first) {  // oppose take left
        PBI my = max_value(coins, start + 2, end);
        left_sum += my.second;
    } else {  // oppose take right
        PBI my = max_value(coins, start + 1, end - 1);
        left_sum += my.second;
    }

    PBI if_right = max_value(coins, start, end - 1);
    int right_sum = coins[end];
    if (if_right.first) {  // oppose take left
        PBI my = max_value(coins, start + 1, end - 1);
        right_sum += my.second;
    } else {  // oppose take right
        PBI my = max_value(coins, start, end - 2);
        right_sum += my.second;
    }

    if (left_sum > right_sum) {
        memo[start][end] = std::make_pair(true, left_sum);
        return memo[start][end];
    } else {
        memo[start][end] = std::make_pair(false, right_sum);
        return memo[start][end];
    }
}


void testcase() {
    int n; std::cin >> n;
    VI coins(n);
    memo = VVP(n, std::vector<PBI>(n, std::make_pair(false, -1)));
    for (int i = 0; i < n; ++i)
        std::cin >> coins[i];
    PBI res = max_value(coins, 0, n - 1);
    std::cout << res.second << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}