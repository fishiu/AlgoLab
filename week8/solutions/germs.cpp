#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Triangulation = CGAL::Delaunay_triangulation_2<K>;

void testcase(int bnum) {
    int l, b, r, t;
    std::cin >> l >> b >> r >> t;

    std::vector<K::Point_2> pts;
    for (int i = 0; i < bnum; ++i) {
        int x, y; std::cin >> x >> y;
        pts.emplace_back(x, y);
    }

    Triangulation tri;
    tri.insert(pts.begin(), pts.end());

    // find the radius when a bac first hit
    std::vector<double> die_radius;
    for (auto v = tri.finite_vertices_begin(); v != tri.finite_vertices_end(); ++v) {
        double x = v->point().x();
        double y = v->point().y();
        double min_dish = std::min({std::abs(x - l), std::abs(x - r), std::abs(y - b), std::abs(y - t)});

        double min_bac_sqrd = std::numeric_limits<double>::max();
        auto edge_c = tri.incident_edges(v);  // edge circulator
        if (edge_c != nullptr) {
            do {
                if (tri.is_infinite(edge_c)) continue;
                min_bac_sqrd = std::min(min_bac_sqrd, tri.segment(edge_c).squared_length());
            } while (++edge_c != tri.incident_edges(v));
        }
        // be very careful
        die_radius.push_back(std::min(min_dish, std::sqrt(min_bac_sqrd) / 2) - 0.5);
    }

    // sort die_radius
    std::sort(die_radius.begin(), die_radius.end());
    std::cout << std::ceil(std::sqrt(die_radius[0])) << " ";
    std::cout << std::ceil(std::sqrt(die_radius[bnum / 2])) << " ";
    std::cout << std::ceil(std::sqrt(die_radius.back())) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    while (true) {
        int n; std::cin >> n;
        if (n == 0) break;
        testcase(n);
    }

    return 0;
}