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
    int playernum, roundnum;
    std::cin >> playernum >> roundnum;

    // [0, roundnum - 1]
    // [roundnum, roundnum + playernum - 1]
    graph g(roundnum + playernum);
    edge_adder adder(g);

    const vertex_desc source = boost::add_vertex(g);
    const vertex_desc sink = boost::add_vertex(g);

    // match -> player
    for (int i = 0; i < roundnum; ++i) {
        // source -> match
        adder.add_edge(source, i, 1, true);

        int a, b, c;
        std::cin >> a >> b >> c;
        if (c == 1) {  // a win
            adder.add_edge(i, roundnum + a, 1, true);
        } else if (c == 2) {
            adder.add_edge(i, roundnum + b, 1, true);
        } else if (c == 0) {
            adder.add_edge(i, roundnum + a, 1, true);
            adder.add_edge(i, roundnum + b, 1, true);
        }
    }

    // player -> sink
    int sum_score = 0;
    for (int i = 0; i < playernum; ++i) {
        int player_sum = 0; std::cin >> player_sum;
        sum_score += player_sum;
        adder.add_edge(roundnum + i, sink, player_sum, true);
    }

    int result = boost::push_relabel_max_flow(g, source, sink);
    if (result == sum_score && result == roundnum) {
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