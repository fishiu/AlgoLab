#include <iostream>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;

void testcase() {
    int n, e, s, a, b;
    std::cin >> n >> e >> s >> a >> b;
    std::vector<weighted_graph> graphs(s, weighted_graph(n));
    std::vector<weight_map> weight_maps(s);
    for (int i = 0; i < s; ++i)
        weight_maps[i] = boost::get(boost::edge_weight, graphs[i]);

    int u, v, w;
    for (int i = 0; i < e; ++i) {
        std::cin >> u >> v;
        for (int j = 0; j < s; ++j) {
            std::cin >> w;
            boost::add_edge(u, v, w, graphs[j]);
        }
    }

    int h;  // not used
    for (int i = 0; i < s; ++i) {
        std::cin >> h;
    }

    weighted_graph G(n);  // sum graph
    weight_map weight_g = boost::get(boost::edge_weight, G);

    for (int i = 0; i < s; ++i) {
        std::vector<edge_desc> mst;
        boost::kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(mst));
        for (auto mst_edge : mst) {
            int src = (int) boost::source(mst_edge, graphs[i]);
            int tgt = (int) boost::target(mst_edge, graphs[i]);
            // insert only if smaller than
            auto ed = boost::edge(src, tgt, G);
            if (!ed.second || weight_maps[i][mst_edge] < weight_g[ed.first]) {
                boost::add_edge(src, tgt, weight_maps[i][mst_edge], G);
            }
        }
    }

    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, a, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    std::cout << dist_map[b] << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        testcase();

    return 0;
}