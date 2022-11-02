#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

using K = CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt;
using Traits = CGAL::Min_circle_2_traits_2<K>;
using Min_circle = CGAL::Min_circle_2<Traits>;

long ceil_to_double(const K::FT &x) {
    long a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a - 1 >= x) a -= 1;
    return a;
}

bool testcase() {
    int n;
    std::cin >> n;
    if (n == 0) return false;  // end case

    std::vector<K::Point_2> P;
    long x, y;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        P.emplace_back(x, y);
    }
    Min_circle mc(P.begin(), P.end(), true);
    const auto &squared_radius = mc.circle().squared_radius();

    long res = ceil_to_double(CGAL::sqrt(squared_radius));
    std::cout << res << std::endl;

    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    bool end_case = true;
    while (end_case)
        end_case = testcase();

    return 0;
}