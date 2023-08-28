#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

class GraphCondensation {
    public:
    size_t vertices;
    size_t edges;
    std::vector<std::vector<size_t>> list, reverse_list;
    std::stack<size_t> ot_order;
    std::vector<bool> passed;
    std::vector<size_t> component;
    std::set<std::pair<size_t, size_t>> cond_edges;
    size_t cnt_components = 0;

    void FillGraph (size_t n, size_t m);
    size_t CountCondensation ();
    void vertex_t_sort(size_t vertex);
    void color_components(size_t vertex);
    size_t CountCondEdges ();
};

int main () {
    GraphCondensation g;
    size_t n, m;
    std::cin >> n >> m;

    g.FillGraph (n, m);
    g.CountCondensation ();
    std:: cout << g.CountCondEdges () << std::endl;
    return 0;
}

void GraphCondensation::FillGraph (size_t n, size_t m) {
    vertices = n;
    edges = m;
    list.resize (n + 1);
    reverse_list.resize (n + 1);
    passed.resize (n + 1);
    component.resize (n + 1);
    size_t b = 0, e = 0;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> b >> e;
        list[b - 1].push_back(e - 1);
        reverse_list[e - 1].push_back(b - 1);
    }
    while (!ot_order.empty()) {
        ot_order.pop();
    }
    
}

void GraphCondensation::vertex_t_sort(size_t vertex) { 
    passed[vertex] = true;
    for (size_t u : list[vertex]) {
        if (!passed[u]) {
            vertex_t_sort(u);
        }
    }
    ot_order.push (vertex);
}

void GraphCondensation::color_components(size_t vertex) {
    component[vertex] = cnt_components;
    for (size_t u : reverse_list[vertex]) {
        if (component[u] == 0){
            color_components(u);
        }
    }
}

size_t GraphCondensation::CountCondensation () {
    for (size_t i = 0; i < vertices; i++) {
        if (!passed[i]) {
            vertex_t_sort(i);
        }
    }
    for (size_t vertex = 0; !ot_order.empty(); ot_order.pop()) {
        vertex = ot_order.top();
        if (component[vertex] == 0) {
            ++cnt_components;
            color_components(vertex);
        }
    }
    return cnt_components;
}

 size_t GraphCondensation::CountCondEdges () {
    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t v : list[i]) {
            if (component[i] != component[v]) {
                cond_edges.insert(std::make_pair(component[i], component[v]));
            }
        }
    }

    return cond_edges.size();
 }

/*
4 4
2 1
3 2
2 3
4 3
*/

/*
4 7
1 1
1 2
2 2
2 3
3 3
3 4
4 4
*/

/*
8 11    
1 2
2 1
2 3
3 4
4 3
4 5
5 6
6 5
4 7
7 8
8 7
*/

/*
5 8
1 2
2 1
2 3
3 4
4 3
4 1
3 5
5 5
*/