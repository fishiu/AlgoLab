#include <iostream>
#include <vector>

#define MAX_N 50001

using VI = std::vector<int>;
using VVI = std::vector<VI>;


// s win: 0, m win: 1
int testcase() {
    int n; std::cin >> n;  // terminal position
    int m; std::cin >> m;  // num of transicions
    int r, b; std::cin >> r >> b;  // red and black position
    VVI graph = VVI(n, VI());
    for (int i = 0; i < m; ++i) {
        int u, v; std::cin >> u >> v;
        graph[u].push_back(v);
    }

    // the first (subscription=0) is not used
    VI mini(n + 1, MAX_N);
    VI maxi(n + 1, -1);

    mini[n] = 0;
    maxi[n] = 0;

    for (int i = n - 1; i >= 1; --i) {
        for (int j: graph[i]) {
            mini[i] = std::min(mini[i], maxi[j] + 1);
            maxi[i] = std::max(maxi[i], mini[j] + 1);
        }
    }

    int sherlock = mini[r];
    int moriaty = mini[b];

    if (sherlock < moriaty)
        return 0;
    if (moriaty < sherlock)
        return 1;
    if (sherlock % 2 == 1)  // r b b r r b ...
        return 0;
    return 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        std::cout << testcase() << std::endl;

    return 0;
}