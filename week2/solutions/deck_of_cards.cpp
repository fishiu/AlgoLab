#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using VI = std::vector<int>;
using PI = std::pair<int, int>;
using VP = std::vector<PI>;
using MI = std::unordered_map<int, int>;

VI::const_iterator find_close(const VI &vec, int val) {
    auto iter_geq = std::lower_bound(vec.begin(), vec.end(), val);
    if (iter_geq == vec.begin()) {
        return iter_geq;
    }

    int prev = *(iter_geq - 1);
    int geq = *iter_geq;
    if (std::abs(prev - val) <= std::abs(geq - val)) {
        return iter_geq - 1;
    } else {
        return iter_geq;
    }
}

struct PairLessThan {
    bool operator()(const PI &p1, const PI &p2) const {
        if (p1.first == p2.first) {
            return p1.second < p2.second;
        } else {
            return p1.first < p2.first;
        }
    }
};

void testcase() {
    int n; std::cin >> n;
    int target; std::cin >> target;
    VI numbers(n);
    VI p_sums(n + 1, 0);
    MI psum_map;

    // get prefix sum
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
        if (i >= 1) {
            p_sums[i + 1] = p_sums[i] + numbers[i];
        } else {
            p_sums[i + 1] = numbers[i];
        }
        if (psum_map.count(p_sums[i + 1]) == 0) {
            psum_map.insert(std::make_pair(p_sums[i + 1], i + 1));
        }
    }

    VP candidates(n + 1);  // (abs_diff, idx)
    for (int i = 0; i <= n; ++i) {
        int target_diff_low = p_sums[i] - target;
        int target_diff_up = p_sums[i] + target;
        auto most_close_it_low = find_close(p_sums, target_diff_low);
        auto most_close_it_up = find_close(p_sums, target_diff_up);

        int real_diff_low = std::abs(*most_close_it_low - target_diff_low);
        int real_diff_up = std::abs(*most_close_it_up - target_diff_up);
        int idx;
        if (real_diff_low <= real_diff_up) {
            idx = psum_map[*most_close_it_low];
            candidates[i] = (std::make_pair(real_diff_low, idx));
        }
        else {
            idx = psum_map[*most_close_it_up];
            candidates[i] = (std::make_pair(real_diff_up, idx));
        }
    }

    auto min_cand = std::min_element(candidates.begin(), candidates.end(), PairLessThan());
    int min_cand_idx = min_cand->second;
    int refer_idx = min_cand - candidates.begin();
    if (min_cand_idx < refer_idx) {
        std::cout << min_cand_idx << " " << refer_idx - 1 << std::endl;
    } else {
        std::cout << refer_idx << " " << min_cand_idx - 1 << std::endl;
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;  // test cases number
    while (t--)
        testcase();

    return 0;
}