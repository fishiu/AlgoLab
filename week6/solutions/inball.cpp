#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long round_down(const CGAL::Quotient<ET> &val) {
    double a = std::floor(CGAL::to_double(val));
    while (a > val) a--;
    while (a + 1 <= val) a++;
    return (long) a;
}

void solve(int enq_num, int d) {
    const int radius_id = d;
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    for (int enq_id = 0; enq_id < enq_num; enq_id++) {
        int norm_sqr = 0;
        for (int var_id = 0; var_id < d; var_id++) {
            int a; std::cin >> a;
            norm_sqr += a * a;
            lp.set_a(var_id, enq_id, a);
        }
        // it is guaranteed to be int (very strong assumption)
        int norm = std::sqrt(norm_sqr);
        lp.set_a(radius_id, enq_id, norm);
        int b; std::cin >> b;
        lp.set_b(enq_id, b);
    }
    lp.set_l(radius_id, true, 0);
    lp.set_c(radius_id, -1);

    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible()) {
        std::cout << "none";
    } else if (s.is_unbounded()) {
        std::cout << "inf";
    } else {
        std::cout << round_down(-s.objective_value());
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    while (true) {
        int enq_num, d;
        std::cin >> enq_num;
        if (enq_num == 0) break;
        std::cin >> d;
        solve(enq_num, d);
    }
}