#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

namespace boost {
    struct edge_component_t {
        // enum { num = 555 };
        typedef edge_property_tag kind;
    } edge_component;
}


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_component_t, std::size_t>> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::property_map<graph, boost::edge_component_t>::type component_map;

void testcase() {
    int n, m; std::cin >> n >> m;
    graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v; std::cin >> u >> v;
        boost::add_edge(u, v, G);
    }

    component_map comp_map = boost::get(boost::edge_component, G);
    size_t num_comp = biconnected_components(G, comp_map);

    std::vector<std::vector<edge_desc>> comp_edges(num_comp);
    auto ed = boost::edges(G);
    for (auto ei = ed.first; ei != ed.second; ++ei) {
        comp_edges[comp_map[*ei]].push_back(*ei);
    }

    std::vector<std::pair<size_t, size_t>> results;
    for (const auto &comp: comp_edges) {
        if (comp.size() == 1) {
            size_t u, v;
            u = boost::source(comp[0], G);
            v = boost::target(comp[0], G);
            if (v < u) std::swap(u, v);
            results.emplace_back(u, v);
        }
    }

    std::sort(results.begin(), results.end());
    std::cout << results.size() << std::endl;
    for (auto p : results) {
        std::cout << p.first << " " << p.second << std::endl;
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