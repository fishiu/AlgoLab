#include <iostream>
#include <algorithm>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using triangulation = CGAL::Delaunay_triangulation_2<K>;

struct Participant {
    K::Point_2 point;
    int r;
};

void testcase() {
    int m, n; std::cin >> m >> n;
    std::vector<Participant> parts;
    for (int i = 0; i < m; ++i) {
        int x, y, r; std::cin >> x >> y >> r;
        Participant p = {K::Point_2(x, y), r};
        parts.push_back(p);
    }

    int height; std::cin >> height;
    std::vector<K::Point_2> lamps;
    for (int i = 0; i < n; ++i) {
        int x, y; std::cin >> x >> y;
        lamps.emplace_back(x, y);
    }
    triangulation t;
    t.insert(lamps.begin(), lamps.end());

    std::vector<int> die_time(m, -1);  // when each part die (-1 means no die)
    bool no_die_win = false;  // turn true once we found a part no die
    for (int i = 0; i < m; ++i) {
        K::FT r_sum, d_sqrd;  // pre define, used for comparison
        r_sum = parts[i].r + height;
        auto point = parts[i].point;

        if (no_die_win) {
            auto v = t.nearest_vertex(point);
            d_sqrd = CGAL::squared_distance(v->point(), point);
            if (d_sqrd >= r_sum * r_sum)
                std::cout << i << " ";  // no die and win
            continue;
        }

        // no_die not seen yet
        for (int j = 0; j < n; ++j) {  // iterate every lamp by order
            d_sqrd = CGAL::squared_distance(lamps[j], point);
            if (d_sqrd < r_sum * r_sum) {  // die
                die_time[i] = j;
                break;
            }
        }

        if (die_time[i] == -1) {
            no_die_win = true;  // turn true!
            // I first forget to cout this one ...
            std::cout << i << " ";
        }
    }

    if (!no_die_win) {  // find the last die
        int max_time = -1;
        std::vector<int> max_ids;
        for (int i = 0; i < (int) die_time.size(); ++i) {
            if (die_time[i] > max_time) {
                max_time = die_time[i];
                max_ids.clear();
                max_ids.push_back(i);
            } else if (die_time[i] == max_time) {
                max_ids.push_back(i);
            }
        }

        for (const auto i: max_ids) std::cout << i << " ";
    }

    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}