#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;

long round_down(const K::FT& val) {
    double a = std::floor(CGAL::to_double(val));
    while (a > val) a--;
    while (a + 1 <= val) a++;
    return (long) a;
}

long round_up(const K::FT& val) {
    double a = std::ceil(CGAL::to_double(val));
    while (a < val) a++;
    while (a - 1 >= val) a--;
    return (long) a;
}

long round_down2(const K::FT &val) {
    double a = std::floor(CGAL::to_double(val));
    while (a > val) a--;
    while (a < val) a++;
    return (long) a;
}

int main() {
    while (true) {
        int i;
        std::cin >> i;
        double x = i;
        std::cout << i << " " << (int) x << std::endl;
    }

    return 0;
}