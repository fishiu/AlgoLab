#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>

using K = CGAL::Exact_predicates_exact_constructions_kernel;


long ceil_to_double(const K::FT &x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a--;
    while (a + 1 <= x) a++;
    return (long) a;
}

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

    // K::FT min_sq_dist = std::numeric_limits<K::FT>::max();  // fuck the max, which is 0.5
    K::FT min_sq_dist = -1;
    K::Point_2 min_p;
    for (const auto &seg : segs) {
        if (CGAL::do_intersect(ray, seg)) {
            auto inter = CGAL::intersection(ray, seg);
            if (const K::Point_2 *p = boost::get<K::Point_2>(&*inter)) {
                K::FT sq_dist = CGAL::squared_distance(start_p, *p);
                if (sq_dist < min_sq_dist or min_sq_dist == -1) {
                    min_sq_dist = sq_dist;
                    min_p = *p;
                }
            } else if (const K::Segment_2 *col_seg = boost::get<K::Segment_2>(&*inter)) {
                K::FT sq_dist = CGAL::squared_distance(start_p, col_seg->source());
                if (sq_dist < min_sq_dist or min_sq_dist == -1) {
                    min_sq_dist = sq_dist;
                    min_p = col_seg->source();
                }
                sq_dist = CGAL::squared_distance(start_p, col_seg->target());
                if (sq_dist < min_sq_dist or min_sq_dist == -1) {
                    min_sq_dist = sq_dist;
                    min_p = col_seg->target();
                }
            }
        }
    }

    if (min_sq_dist == -1) {
        std::cout << "no" << std::endl;
    } else {
        long res_x = ceil_to_double(min_p.x());
        long res_y = ceil_to_double(min_p.y());
        std::cout << res_x << " " << res_y << std::endl;
    }
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