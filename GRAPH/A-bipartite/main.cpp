#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

class Graph {
    public:
    std::vector<std::vector <int>> list;
    void GetGraph ();
    void PrintGraph ();
    bool IsBipartite (char* color, int vertex);
};

bool IsBipartite (Graph& graph);

int main () {
    Graph g;
    g.GetGraph();
    std::cout << ((IsBipartite(g) == true) ? "YES" : "NO"); 
    std::cout << std::endl;  
    return 0;
}

void Graph::GetGraph () {
    int n, m;
    std::cin >> n >> m;
    list.resize(n);
    int first, second;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> first >> second;
        list[first].push_back(second);
        list[second].push_back(first);
    }
}

void Graph::PrintGraph() {
    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t j = 0; j < list[i].size(); ++j) {
            std::cout << list[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void PrintChar (char* c, size_t size);

bool IsBipartite (Graph& graph) {
    char* color = new char[graph.list.size() + 1];
    for (size_t k = 0; k < graph.list.size(); ++k){
        color[k] = 0;
    }
    
    for (size_t i = 0; i < graph.list.size(); ++i) {
        if (graph.IsBipartite(color, i) == false) {
            return false;
        }
    }

    return true;
}

bool Graph::IsBipartite (char* color, int vertex) {
    if (color[vertex] == 0) {
        color[vertex] = 1;
    } 
    for (size_t i = 0; i < list[vertex].size(); ++i) {
        if (color[list[vertex][i]] == 0) {
            color[list[vertex][i]] = 3 - color[vertex];
            if (IsBipartite(color, list[vertex][i]) == false) {
                return false;
            }
        }
        if (color[list[vertex][i] ] == color[vertex]) {
            return false;
        }
    }
    return true;
}