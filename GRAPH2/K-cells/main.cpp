#include <iostream>
#include <inttypes.h>
#include <cmath>
#include <vector>

class Graph {
    public:
    uint32_t n;
    uint32_t m;
    std::vector<std::pair<std::pair<uint32_t, uint32_t>, uint64_t>> edges;
    
    Graph(uint32_t n_, uint32_t m_) : n(n_), m(m_) {};
    void FillGraph ();
    uint32_t FindComponent (std::vector<uint32_t>& components, uint32_t vertex);
    uint64_t FindMSTMaxEdgeWeight (); 
};



int main () {
    uint32_t n, m;
    std::cin >> n;
    m = n * (n - 1);
    Graph g(n, m);
    g.FillGraph();
    long double ans =  g.FindMSTMaxEdgeWeight();
    std::cout  << std::sqrt(ans) << std::endl;
    return 0;
}

void Graph::FillGraph () {
    std::vector<std::pair<int32_t, int32_t>> cords;
    int32_t x, y;
    for (uint32_t i = 0; i < n; ++i) {
        std::cin >> x >> y;
        cords.push_back(std::make_pair(x, y));
    }

    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            if (i != j) {
                uint64_t cur_dist = (cords[i].first - cords[j].first) * (cords[i].first - cords[j].first) + (cords[i].second - cords[j].second) * (cords[i].second - cords[j].second);
                edges.push_back(std::make_pair(std::make_pair(i, j), cur_dist));
            }
        }
    }
}

uint32_t Graph::FindComponent(std::vector<uint32_t>& components, uint32_t vertex) {
    if (components[vertex] != vertex) {
        components[vertex] = FindComponent(components, components[vertex]);
    }
    return components[vertex];
}

uint64_t Graph::FindMSTMaxEdgeWeight () {
    uint64_t answer = 0;
    std::vector<uint32_t> components;
    std::vector<uint32_t> min_edge;
    std::vector<bool> min_edge_found;
    components.resize(n);
    min_edge.resize(m);
    min_edge_found.resize(m);
    for (size_t i = 0; i < n; ++i) {
        components[i] = i;
    }
    uint32_t trees = n;
    while (trees > 1) {
        for (uint32_t i = 0; i < m; ++i) {
            min_edge_found[i] = false;
        }

        for (uint32_t i = 0; i < m; ++i) {
            uint32_t first_comp = FindComponent(components, edges[i].first.first);
            uint32_t second_comp = FindComponent(components, edges[i].first.second);
            if (first_comp != second_comp) {
                if (min_edge_found[first_comp] == false || edges[min_edge[first_comp]].second > edges[i].second) {
                    min_edge[first_comp] = i;
                    min_edge_found[first_comp] = true;
                }
                if (min_edge_found[second_comp] == false || edges[min_edge[second_comp]].second > edges[i].second) {
                    min_edge[second_comp] = i;
                    min_edge_found[second_comp] = true;
                }
            }
        }

        for (size_t i = 0; i < n; ++i) {
            if (min_edge_found[i] == true) {
                uint32_t st = FindComponent(components, edges[min_edge[i]].first.first);
                uint32_t fn = FindComponent(components, edges[min_edge[i]].first.second);
                if (st != fn) {
                    answer = std::max(answer, edges[min_edge[i]].second);
                    components[st] = fn;
                    min_edge_found[st] = false;
                    min_edge_found[fn] = false; 
                    --trees;
                }
            }
        }
    }

    return answer;
}