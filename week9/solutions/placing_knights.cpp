#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

// BGL graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >	graph;
// Interior Property Maps
typedef	boost::graph_traits<graph>::edge_descriptor			edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;

typedef std::vector<std::vector<int>> VVI;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

class ThreatenAdder {
  public:
    int n;
    const VVI &grid;
    std::vector<std::pair<int, int>> possible_threaten;

    ThreatenAdder(int n, const VVI &grid) : n(n), grid(grid) {}
    
    void add(int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] == 0) return;
        possible_threaten.emplace_back(i, j);
    }

    void clear() {
        possible_threaten.clear();
    }
};

void testcase() {
    int n; std::cin >> n;
    graph G(n * n);
    edge_adder adder(G);
    auto source = boost::add_vertex(G);
    auto sink = boost::add_vertex(G);

    std::vector<std::vector<int>> grid(n, std::vector<int>(n));
    ThreatenAdder tadder(n, grid);

    int valid_n = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int grid_id = i * n + j;
            bool is_black = (i + j) % 2 == 0;  // first grid is black
            int is_present; std::cin >> is_present;
            grid[i][j] = is_present;
            
            if (is_present == 1) {
                valid_n++;

                if (is_black) {
                    adder.add_edge(source, grid_id, 1);
                } else {
                    adder.add_edge(grid_id, sink, 1);
                }

                tadder.clear();
                tadder.add(i - 1, j - 2);
                tadder.add(i - 2, j - 1);
                tadder.add(i - 1, j + 2);
                tadder.add(i - 2, j + 1);

                for (const auto& [i_, j_] : tadder.possible_threaten) {
                    int grid_id_ = i_ * n + j_;
                    if (is_black) {
                        adder.add_edge(grid_id, grid_id_, 1);
                    } else {
                        adder.add_edge(grid_id_, grid_id, 1);
                    }
                }
            }
        }
    }
    
    int max_flow = boost::push_relabel_max_flow(G, source, sink);  // also min vc
    std::cout << valid_n - max_flow << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

	return 0;
}
