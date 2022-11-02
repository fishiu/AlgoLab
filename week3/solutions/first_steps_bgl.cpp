#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <algorithm>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int> > weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

void testcase() {
    int n, m;
    std::cin >> n >> m;
    weighted_graph G(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        boost::add_edge(u, v, w, G);
    }

    // mimimun spanning tree
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

    int weight_sum = 0;
    for (edge_desc e: mst) {
        weight_sum += boost::get(boost::edge_weight, G, e);
    }
    std::cout << weight_sum << " ";

    // furthest node from 0
    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, 0, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    int max_dist = 0;
    for (int i = 1; i < n; i++) {
        if (dist_map[i] > max_dist) {
            max_dist = dist_map[i];
        }
    }
    std::cout << max_dist << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}