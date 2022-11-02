# San Francisco

```c++
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
```

## My ideas

### What is the problem?

(concise description/definition, no story)

It is about making certain number of moves through holes (nodes) and gaining different scores marked on the respective canal (edge).

### How do you model it?

What mathematical concepts do you use to formally describe and reason about (and eventually solve) the problem?

It can be modeled into a graph problem (weighted directed graph). We need to find a path from a given starting point and our score is the sum of weights of all the edges consisting the path. Our goal is to maximize the score with the given path length. There are two special things:

- If we find the score already exeeds a given score, we can simply break and report the step number.
- There are special nodes in the graph called Weayaya, which are nodes with no outgoing edge. When making moves, we can jump from a Weayaya node directly to the starting point. The jumping action will not be counted in the length of the path.

### How do you algorithmically solve it?

Describe the algorithm, first in a rough overview, and then selectively in more detail. Analyze the runtime.

I use dynamic programming. We want to get the maximum score `dp[i][j]` at position `j` when we have made `i` steps. This dp process follows the **Non-aftereffect rule** and **Optimal sub-problem**: `max = std::max(dp[step - 1][in.first] + in.second, max);`

Runtime: $\Theta(STEP \cdot NODE^2)$

### How do you implement and test it?

Explain the most interesting steps relevant for your implementation. Only here you may refer to the printout of the code you brought.

I use bottom-up DP (incrementing steps and positions). The main data structures are two vector to store edge information (adjacent list), and a Weayaya bool vector.

1. Find the Weayaya nodes.

2. Calculate DP.

   ```c++
   for (const auto &in: in_edge[point])
   	if (dp[step - 1][in.first] != -1)
   		max = std::max(dp[step - 1][in.first] + in.second, max);
   dp[step][point] = max;
   ```

3. Update starting point at the end of each iteration.

   ```c++
   if (is_weayaya[point])
   	dp[step][0] = std::max(dp[step][0], dp[step][point]);
   ```

### Overall

What challenges did you face in these different phases and how did you overcome them? What was most difficult for you during the process?

How to handle the Weayaya point: just update after the iteration. (Analysing the coherent feature of Weayaya point).

I first used `int` which does not fit the input numbers and overflow occurred. I change to `long` and it is fine.