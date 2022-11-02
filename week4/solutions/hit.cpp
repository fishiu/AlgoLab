#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;


void testcase(int n) {
    long x, y, a, b; std::cin >> x >> y >> a >> b;
    K::Point_2 start_p(x, y), second_p(a, b);  // starting point, ray point
    K::Ray_2 ray(start_p, second_p);

    std::vector<K::Segment_2> segs;  // obstacles
    long r, s, t, u;
    for (int i = 0; i < n; ++i) {
        std::cin >> r >> s >> t >> u;
        segs.emplace_back(K::Point_2(r, s), K::Point_2(t, u));
    }
    // random shuffle
    std::random_shuffle(segs.begin(), segs.end());

    for (const auto &seg : segs) {
        if (CGAL::do_intersect(ray, seg)) {
            std::cout << "yes" << std::endl;
            return;
        }
    }

    std::cout << "no" << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    while (true) {
        int n; std::cin >> n;
        if (n == 0)
            break;  // end case
        testcase(n);
    }

    return 0;
}