#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long round_up(const CGAL::Quotient<ET> &val) {
    double a = std::ceil(CGAL::to_double(val));
    while (a > val) a--;
    while (a < val) a++;
    return (long) a;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    while (true) {
        int p, a, b; std::cin >> p;
        if (p == 0) break;
        std::cin >> a >> b;

        Solution s;
        if (p == 1) {  // max problem
            Program lp(CGAL::SMALLER, true, 0, false, 0);

            const int X = 0;
            const int Y = 1;
            lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);
            lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a * b);
            lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);

            lp.set_c(X, a); lp.set_c(Y, -b);

            s = CGAL::solve_linear_program(lp, ET());
        } else if (p == 2) {
            Program lp(CGAL::SMALLER, false, 0, true, 0);

            const int X = 0;
            const int Y = 1;
            const int Z = 2;
            lp.set_a(X, 0, -1); lp.set_a(Y, 0, -1); lp.set_b(0, 4);
            lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a * b);
            lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_b(2, 1);

            lp.set_c(X, a); lp.set_c(Y, b); lp.set_c(Z, 1);

            s = CGAL::solve_linear_program(lp, ET());
        }

        if (s.is_infeasible()) {
            std::cout << "no";
        } else if (s.is_unbounded()) {
            std::cout << "unbounded";
        } else {
            if (p == 1)
                std::cout << -round_up(s.objective_value());
            else
                std::cout << round_up(s.objective_value());
        }

        std::cout << std::endl;
    }

    return 0;
}