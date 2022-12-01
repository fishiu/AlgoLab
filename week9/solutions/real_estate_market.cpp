#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

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
    int num_buyer, num_site, num_state;
    std::cin >> num_buyer >> num_site >> num_state;

    graph G(num_buyer + num_site + num_state);
    auto src = boost::add_vertex(G);
    auto sink = boost::add_vertex(G);
    edge_adder adder(G);

    for (int i = 0; i < num_state; i++) {
        int state_limit;
        std::cin >> state_limit;
        int state_id = num_buyer + num_site + i;
        adder.add_edge(state_id, sink, state_limit, 0);
    }

    for (int i = 0; i < num_site; i++) {
        int belong_state; std::cin >> belong_state;
        int site_id = num_buyer + i;
        int state_id = num_buyer + num_site + belong_state - 1;
        adder.add_edge(site_id, state_id, 1, 0);
    }

    for (int i = 0; i < num_buyer; i++) {
        std::vector<int> bids_from_i(num_site);
        for (int j = 0; j < num_site; j++)
            std::cin >> bids_from_i[j];
        int max_bid = *(std::max_element(bids_from_i.begin(), bids_from_i.end()));
        for (int j = 0; j < num_site; j++) {
            int site_id = num_buyer + j;
            int cost = -bids_from_i[j];
            adder.add_edge(i, site_id, 1, cost);
        }
        adder.add_edge(src, i, 1, 0);
    }

    // boost::successive_shortest_path_nonnegative_weights(G, src, sink);
    // long cost = boost::find_flow_cost(G);
    // std::cout <<   << std::endl;

    int flow = boost::push_relabel_max_flow(G, src, sink);
    boost::cycle_canceling(G);
    int cost = boost::find_flow_cost(G);
    std::cout << flow << " " << -cost << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}
