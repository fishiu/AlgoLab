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
    int v_num, e_num, store_num;
    std::cin >> v_num >> e_num >> store_num;

    graph g(v_num);
    edge_adder adder(g);
    const vertex_desc target = boost::add_vertex(g);

    // add store -> target
    for (int i = 0; i < store_num; ++i) {
        int store_vid; std::cin >> store_vid;
        adder.add_edge(store_vid, target, 1, true);
    }

    // add common edges
    for (int i = 0; i < e_num; ++i) {
        int from, to; std::cin >> from >> to;
        adder.add_edge(from, to, 1, false);
    }

    int result = boost::push_relabel_max_flow(g, 0, target);
    if (result == store_num) {
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