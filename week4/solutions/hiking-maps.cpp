#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>
#include <map>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;

class Counter : public std::map<int, int> {
public:
    void add(int i) {
        auto it = find(i);
        if (it == end())
            insert({i, 1});
        else
            ++it->second;
    }

    void remove(int i) {
        auto it = find(i);
        if (--it->second == 0)
            erase(it);
    }

    bool is_full (size_t total_num) {
        return size() == total_num;
    }

    void debug() {
        for (const auto &p : *this)
            std::cout << p.first << ": " << p.second << std::endl;
    }
};

void testcase() {
    int point_num, map_num; std::cin >> point_num >> map_num;  // point num, map num
    int leg_num = point_num - 1;  // leg num

    std::vector<K::Point_2> points;
    for (int i = 0; i < point_num; ++i) {
        long x, y; std::cin >> x >> y;
        points.emplace_back(x, y);
    }
    std::vector<std::vector<int>> inside_triangle(map_num);  // whether leg k is inside
    for (int i = 0; i < map_num; ++i) {
        long x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
        std::cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;
        K::Point_2 p0(x0, y0), p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4), p5(x5, y5);

        K::Line_2 l0(p0, p1);
        if (l0.oriented_side(p2) < 0)
            l0 = K::Line_2(p1, p0);

        K::Line_2 l1(p2, p3);
        if (l1.oriented_side(p0) < 0)
            l1 = K::Line_2(p3, p2);

        K::Line_2 l2(p4, p5);
        if (l2.oriented_side(p0) < 0)
            l2 = K::Line_2(p5, p4);

        bool last = false;
        for (int j = 0; j < point_num; ++j) {
            auto p = points[j];
            if (l0.oriented_side(p) >= 0 && l1.oriented_side(p) >= 0 && l2.oriented_side(p) >= 0) {
                if (last)
                    inside_triangle[i].push_back(j - 1);
                last = true;
            } else {
                last = false;
            }
        }
    }

    int min_map_num = map_num;
    Counter counter;
    int left_p = 0, right_p = 0;
    // while (right_p < map_num) {
    //     if (!counter.is_full(leg_num)) {
    //         for (auto i : inside_triangle[right_p])
    //             counter.add(i);
    //         ++right_p;
    //     } else {  // full
    //         min_map_num = std::min(min_map_num, right_p - left_p);
    //         for (auto i : inside_triangle[left_p])
    //             counter.remove(i);
    //         ++left_p;
    //     }
    //     // std::cout << "left_p: " << left_p << ", right_p: " << right_p << ". ";
    //     // counter.debug();
    // }

    while (right_p < map_num) {
        while (!counter.is_full(leg_num) && right_p < map_num) {
            for (auto i : inside_triangle[right_p])
                counter.add(i);
            ++right_p;
        }
        if (counter.is_full(leg_num)) {
            while (counter.is_full(leg_num) && left_p < right_p) {
                for (auto i : inside_triangle[left_p])
                    counter.remove(i);
                ++left_p;
            }
            min_map_num = std::min(min_map_num, right_p - left_p + 1);
        }
    }

    std::cout << min_map_num << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}