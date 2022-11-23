<h1 style="text-align: center">Suez</h1>

<div style="text-align: right">Xiaoyuan Jin, Nov 17</div>

```c++
#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct point {
    int x;
    int y;
};

typedef std::vector<point> VP;

long round_up(const CGAL::Quotient<ET> &val) {
    double a = std::ceil(CGAL::to_double(val));
    while (a < val) a++;
    while (a - 1 >= val) a--;
    return (long) a;
}

void testcase() {
    int new_num, old_num, h, w;
    std::cin >> new_num >> old_num >> h >> w;
    VP new_points;
    VP old_points;

    Program lp(CGAL::SMALLER, true, 1, false, 0);

    for (int i = 0; i < new_num; ++i) {
        int x, y;
        std::cin >> x >> y;
        new_points.push_back({x, y});
        lp.set_c(i, -2 * (h + w));  // maximize perimeter
    }
    for (int i = 0; i < old_num; ++i) {
        int x, y;
        std::cin >> x >> y;
        old_points.push_back({x, y});
    }

    // create functions between new points
    int ine_id = 0;
    for (int i = 0; i < new_num; ++i) {
        for (int j = i + 1; j < new_num; ++j) {
            int diff_x = std::abs(new_points[i].x - new_points[j].x);
            int diff_y = std::abs(new_points[i].y - new_points[j].y);
            // very tricky here, actually, there are two inequality
            ET val_b = std::max(ET(2 * diff_x, w), ET(2 * diff_y, h));
            lp.set_a(i, ine_id, 1);
            lp.set_a(j, ine_id, 1);
            lp.set_b(ine_id, val_b);
            ine_id++;
        }
    }

    for (int i = 0; i < new_num; ++i) {
        ET min_to_old = ET(std::numeric_limits<double>::max());
        for (int j = 0; j < old_num; ++j) {
            int diff_x = std::abs(new_points[i].x - old_points[j].x);
            int diff_y = std::abs(new_points[i].y - old_points[j].y);
            ET val_b = std::max(ET(2 * diff_x, w) - 1, ET(2 * diff_y, h) - 1);
            min_to_old = std::min(val_b, min_to_old);
        }
        lp.set_u(i, true, min_to_old);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_unbounded()) {
        std::cout << "unbounded" << std::endl;
    } else {
        std::cout << round_up(-s.objective_value()) << std::endl;
    }
}
```

### What is the problem?

To maximize the perimeter, essentially equals to maximize the sum of all scale coefficient of new posters while maintaining a non-overlap constriant.

### How do you model it?

It is a linear programming problem. There are two kinds of constriants: new ~ new, new ~ old.

The subproblem is to discover when two posters will overlap. There will be two situations: first hit horizontally or vertically. It can be modeled as:

To ensure no hit horiontally: $(a_1 + a_2) \times \dfrac{w}{2} \leq diff_x$, only when $\dfrac{diff_x}{w}$ is dominant

To ensure no hit vertically: $(a_1 + a_2) \times \dfrac{h}{2} \leq diff_y$, only when $\dfrac{diff_y}{h}$ is dominant

Only the bigger one need to be followed (though seemed not intuitive)

$a_i + a_j \leq max(\dfrac{2 * diff_x}{w}, \dfrac{2 * diff_y}{h})$

### How do you algorithmically solve it?

Variables(a) are the scale coefficient of new posters.

`new_num * new_num` ineuqlities for new ~ new. Complexity: $NewNum * NewNum \leq 30 * 30$

`new_num` upper bounds for each new (since old poster are fixed, no need to introduce new variables), there is a min-max computation. Complexity: $\Theta(NewNum * OldNum) \leq 30 * 10^3$

### How do you implement and test it?

See code, be careful about variable boundaries.