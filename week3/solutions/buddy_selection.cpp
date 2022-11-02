#include <iostream>
#include <set>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

std::string testcase() {
    int n, c;
    unsigned int f;
    std::cin >> n >> c >> f;
    std::vector<std::set<std::string>> char_vec(n, std::set<std::string>());
    weighted_graph G(n);
    for (int i = 0; i < n; ++i) {
        std::string ch;
        for (int j = 0; j < c; ++j) {
            std::cin >> ch;
            char_vec[i].insert(ch);
        }  // get all characters of i
        for (int j = 0; j < i; ++j) {
            std::vector<std::string> intersection;
            std::set_intersection(char_vec[i].begin(), char_vec[i].end(), char_vec[j].begin(), char_vec[j].end(), std::back_inserter(intersection));
            if (intersection.size() > f) {
                boost::add_edge(i, j, G);
            }
        }
    }  // graph constructed

    unsigned int num_v = boost::num_vertices(G);
    std::vector<vertex_desc> mate_map(n); // exterior property map
    boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    unsigned int matching_size = boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    if (2 * matching_size == num_v) {  // maximum match
        return "not optimal";
    } else {
        return "optimal";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--)
        std::cout << testcase() << std::endl;

    return 0;
}