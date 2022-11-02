#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int read_int() {
    int a; std::cin >> a;
    return a;
}

long round_down(const CGAL::Quotient<ET> &val) {
    double a = std::floor(CGAL::to_double(val));
    while (a > val) a--;
    while (a + 1 <= val) a++;
    return (long) a;
}

void testcase(int nut_num, int food_num) {
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    for (int i = 0; i < nut_num; ++i) {
        const int min = read_int();
        const int max = read_int();
        lp.set_b(2 * i, -min);
        lp.set_b(2 * i + 1, max);
    }

    for (int i = 0; i < food_num; ++i) {
        const int price = read_int();
        lp.set_c(i, price);
        for (int j = 0; j < nut_num; ++j) {
            const int nut_content = read_int();
            lp.set_a(i, 2 * j, -nut_content);
            lp.set_a(i, 2 * j + 1, nut_content);
        }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible())
        std::cout << "No such diet." << std::endl;
    else
        std::cout << round_down(s.objective_value()) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n, m;
    while (true) {
        std::cin >> n >> m;
        if (n == 0 && m == 0) break;
        testcase(n, m);
    }

    return 0;
}