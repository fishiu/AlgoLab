#include <iostream>
#include <string>
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
    int paperh, paperw;
    std::cin >> paperh >> paperw;

    std::string target_str; std::cin >> target_str;
    graph g(26 * 26 + 26);
    edge_adder adder(g);
    const vertex_desc source = boost::add_vertex(g);
    const vertex_desc sink = boost::add_vertex(g);

    for (int i = 0; i < 26; ++i) {
        char count_obj = 'A' + i;
        int count_res = std::count(target_str.begin(), target_str.end(), count_obj);
        adder.add_edge(26 * 26 + i, sink, count_res, true);
    }

    std::vector<std::string> front_lines(paperh);
    std::vector<std::string> back_lines(paperh);
    for (int i = 0; i < paperh; ++i)
         std::cin >> front_lines[i];
    for (int i = 0; i < paperh; ++i)
         std::cin >> back_lines[i];

    std::vector<int> save_node_in(26 * 26, 0);
    for (int i = 0; i < paperh; ++i) {
        for (int j = 0; j < paperw; ++j) {
            int front_char_to_i = front_lines[i][j] - 'A';
            int back_char_to_i = back_lines[i][paperw - j - 1] - 'A';
            int node_id = front_char_to_i * 26 + back_char_to_i;
            save_node_in[node_id] += 1;
        }
    }

    for (int front_i = 0; front_i < 26; ++front_i) {
        for (int back_i = 0; back_i < 26; ++back_i) {
            int node_id = front_i * 26 + back_i;
            if (save_node_in[node_id] == 0) continue;
            adder.add_edge(source, node_id, save_node_in[node_id], true);

            adder.add_edge(node_id, 26 * 26 + front_i, save_node_in[node_id], true);
            adder.add_edge(node_id, 26 * 26 + back_i, save_node_in[node_id], true);
        }
    }

    int result = boost::push_relabel_max_flow(g, source, sink);
    if (result == int (target_str.size())) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
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