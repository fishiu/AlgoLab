#include <iostream>
#include <algorithm>
#include <vector>

using VI = std::vector<long long int>;
using PI = std::pair<long long int, long long int>;
using VP = std::vector<PI>;
using VVP = std::vector<VP>;
using VVI = std::vector<VI>;

void testcase() {
    long long int n, m, x, k;
    std::cin >> n >> m >> x >> k;

    VVP in_edge(n, VP());
    VVP out_edge(n, VP());
    VVI dp(k + 1, VI(n, -1));
    std::vector<bool> is_weayaya(n, false);

    for (int i = 0; i < m; ++i) {
        int u, v, w; std::cin >> u >> v >> w;
        out_edge[u].push_back(std::make_pair(v, w));
        in_edge[v].push_back(std::make_pair(u, w));
    }

    for (int i = 0; i < n; ++i) {
        if (out_edge[i].empty())
            is_weayaya[i] = true;
    }

    dp[0][0] = 0;  // initially, we score 0 at position 0
    for (int step = 1; step <= k; ++step) {
        for (int point = 0; point < n; ++point) {
            long long int max = -1;
            for (const auto &in: in_edge[point])
                if (dp[step - 1][in.first] != -1)
                    max = std::max(dp[step - 1][in.first] + in.second, max);
            // get dp node result
            dp[step][point] = max;
            // if weayaya, update 0 point
            if (is_weayaya[point])
                dp[step][0] = std::max(dp[step][0], dp[step][point]);
        }

        if (*std::max_element(dp[step].begin(), dp[step].end()) >= x) {
            std::cout << step << std::endl;
            return;
        }
    }

    std::cout << "Impossible" << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}