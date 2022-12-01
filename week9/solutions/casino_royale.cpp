#include <iostream>
#include <vector>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

#define M 12800000

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void testcase() {
    int num_stop, num_task, limit; std::cin >> num_stop >> num_task >> limit;
    graph G(num_task + num_stop);
    auto source = boost::add_vertex(G);
    edge_adder adder(G);

    adder.add_edge(source, 0, limit, 0);
    for (int i = 1; i < num_stop; ++i)
        adder.add_edge(i - 1, i, limit, 128);

    for (int i = 0; i < num_task; ++i) {
        int node_id = num_stop + i;
        long q;
        int a, b; std::cin >> a >> b >> q;
        adder.add_edge(a, node_id, 1, (b - a) * 128 - q);
        adder.add_edge(node_id, b, 1, 0);
    }

    boost::successive_shortest_path_nonnegative_weights(G, source, num_stop - 1);
    long cost = boost::find_flow_cost(G);
    std::cout << limit * (num_stop - 1) * 128 - cost  << std::endl;

    // boost::push_relabel_max_flow(G, source, num_stop - 1);
    // boost::cycle_canceling(G);
    // int cost = boost::find_flow_cost(G);
    // std::cout << -cost << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}
