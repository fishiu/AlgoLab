#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Triangulation = CGAL::Delaunay_triangulation_2<K>;

void testcase(int n) {
    std::vector<K::Point_2> pts;
    for (int i = 0; i < n; ++i) {
        int x, y; std::cin >> x >> y;
        pts.emplace_back(x, y);
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    int m; std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; std::cin >> x >> y;
        auto p = K::Point_2(x, y);
        auto v = t.nearest_vertex(p);
        K::Point_2 q = v->point();
        std::cout << (long) CGAL::squared_distance(p, q) << std::endl;
    }
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