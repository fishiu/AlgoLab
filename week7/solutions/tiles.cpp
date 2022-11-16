#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using traits = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_capacity_t, int,
                boost::property<boost::edge_residual_capacity_t, int,
                        boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

class edge_adder {
    graph &g;

public:
    explicit edge_adder(graph &g) : g(g) {}

    void add_edge(int from, int to, int capacity, bool is_directed) {
        auto c_map = boost::get(boost::edge_capacity, g);
        auto r_map = boost::get(boost::edge_reverse, g);
        const auto e = boost::add_edge(from, to, g).first;
        const auto rev_e = boost::add_edge(to, from, g).first;
        c_map[e] = capacity;
        c_map[rev_e] = is_directed ? 0 : capacity;
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

void testcase() {
    int gridw, gridh;
    std::cin >> gridw >> gridh;

    graph g(gridw * gridh);
    edge_adder adder(g);

    const vertex_desc source = boost::add_vertex(g);
    const vertex_desc sink = boost::add_vertex(g);

    std::vector<char> chars(gridh * gridw);
    int free_cnt = 0;
    for (int i = 0; i < gridh; ++i) {
        for (int j = 0; j < gridw; ++j) {
            int cid = i * gridw + j;
            std::cin >> chars[cid];
            if (chars[cid] != '.') continue;
            free_cnt++;

            if ((i + j) % 2 == 0) {  // black
                adder.add_edge(source, cid, 1, true);
            } else {
                adder.add_edge(cid, sink, 1, true);
            }

            int top = (i - 1) * gridw + j;
            int left = i * gridw + j - 1;

            if (i > 0 && chars[top] == '.') {
                if ((i + j) % 2 == 0) {  // black
                    adder.add_edge(cid, top, 1, true);
                } else {
                    adder.add_edge(top, cid, 1, true);
                }
            }
            if (j > 0 && chars[left] == '.') {
                if ((i + j) % 2 == 0) {  // black
                    adder.add_edge(cid, left, 1, true);
                } else {
                    adder.add_edge(left, cid, 1, true);
                }
            }
        }
    }

    if (free_cnt % 2 != 0 ) {
        std::cout << "no" << std::endl;
        return;
    }

    int result = boost::push_relabel_max_flow(g, source, sink);
    if (result == free_cnt / 2) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}