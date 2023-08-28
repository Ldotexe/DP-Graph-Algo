#include <iostream>
#include <inttypes.h>
#include <vector>

struct DfsStruct {
    std::vector<size_t> tin, tout;
    std::vector<bool> color;
    size_t time;
};

class Graph {
    public:
    uint32_t n;
    std::vector<std::vector<uint32_t>> list;

    void FillGraph ();
    std::vector<std::pair<uint32_t, uint32_t>> Findbridges (DfsStruct* dfs);
    void DfsBridge (uint32_t parent, uint32_t vertex, DfsStruct* dfs, std::vector<std::pair<uint32_t, uint32_t>>& bridges);
    void DeleteBridges ();
    void PrintGraph ();
    uint32_t ColorGraph (std::vector<uint32_t>* color);
    void ColorDfs (uint32_t vertex, uint32_t color_number, std::vector<uint32_t>* color);
    bool CheckPlanar ();
    Graph GetColorGraph (uint32_t color, std::vector<uint32_t> colors);
    std::vector<uint32_t> FindCicle ();
};

int main () {
    Graph g;
    g.FillGraph();
    std::cout << g.CheckPlanar() << std::endl;
    return 0;
}

void Graph::FillGraph () {
    size_t m;
    std::cin >> n >> m;
    list.resize(n + 1);
    for (size_t i = 0; i < m; ++i) {
        size_t first, second;
        std::cin >> first >> second;
        list[first].push_back (second);
        list[second].push_back (first);
    }
}

void Graph::DeleteBridges () {
    DfsStruct dfs;
    std::vector<std::pair<uint32_t, uint32_t>> bridges = Findbridges(&dfs);
    std::cout << "Bridges found: " << bridges.size() << std::endl;
    for (size_t i = 0; i < bridges.size(); ++i) {
        uint32_t first = bridges[i].first, second = bridges[i].second;
        std::cout << "Bridge:" << first << " " << second << std::endl;
        for (size_t k = 0; k < 2; ++k) {
            for (size_t j = 0; j < list[first].size() - 1; ++j) {
                if (list[first][j] == second) {
                    std::swap(list[first][j], list[first][j + 1]);
                }
            }
            if (list[first][list[first].size() - 1] == second) {
                list[first].pop_back();
            }
            std::swap (first, second);
        }
    }
}

std::vector<std::pair<uint32_t, uint32_t>> Graph::Findbridges (DfsStruct* dfs) {
    std::vector<std::pair<uint32_t, uint32_t>> answer;
    dfs->tin.resize (n + 1);
    dfs->tout.resize (n + 1);
    dfs->color.resize (n + 1);
    dfs->time = 0;

    for (size_t i = 0; i < n + 1; ++i) {
        dfs->color[i] = 0;
    }
    for (size_t i = 1; i < list.size(); ++i) {
        if (dfs->color[i] == 0) {
            DfsBridge (0, i, dfs, answer);
        }
    }
    return answer;
}

void Graph::DfsBridge (uint32_t parent, uint32_t vertex, DfsStruct* dfs, std::vector<std::pair<uint32_t, uint32_t>>& bridges) {
    dfs->color[vertex] = 1;
    ++dfs->time;
    dfs->tin[vertex]  = dfs->time;
    dfs->tout[vertex] = dfs->time;

    for (auto adjacent_vertex : list[vertex]) {
        if (adjacent_vertex == parent) {
            continue;
        }
        if (dfs->color[adjacent_vertex] == 0) {
            DfsBridge (vertex, adjacent_vertex, dfs, bridges);
            dfs->tout[vertex] = std::min (dfs->tout[vertex], dfs->tout[adjacent_vertex]);
            if (dfs->tin[vertex] < dfs->tout[adjacent_vertex]) {
                bridges.push_back(std::make_pair(vertex, adjacent_vertex));
            }
        }
        else {
            dfs->tout[vertex] = std::min (dfs->tout[vertex], dfs->tin[adjacent_vertex]);
        }
    }
}

void Graph::PrintGraph() {
    for (size_t i = 1; i < n + 1; ++i) {
        std::cout << i << ": ";
        for (size_t j = 0; j < list[i].size(); ++j) {
            std::cout << list[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::ColorDfs (uint32_t vertex, uint32_t color_number, std::vector<uint32_t>* color) {
    (*color)[vertex] = color_number;
    for (uint32_t i : list[vertex]) {
        if ((*color)[i] == 0) {
            ColorDfs (i, color_number, color);
        }
    }
}

uint32_t Graph::ColorGraph (std::vector<uint32_t>* color) {
    (*color).resize(n + 1);
    for (size_t i = 0; i < n + 1; ++i) {
        (*color)[i] = 0;
    }
    uint32_t color_number = 0;
    for (size_t i = 1; i < n + 1; ++i) {
        if ((*color)[i] == 0) {
            ++color_number;
            ColorDfs(i, color_number, color);
        }
    }
    return color_number;
}

Graph Graph::GetColorGraph (uint32_t color, std::vector<uint32_t> colors) {
    Graph color_graph;
    color_graph.n = n;
    color_graph.list.resize (n + 1);
    for (uint32_t i = 1; i < n + 1; i++) {
        if (colors[i] == color) {
            color_graph.list[i] = list[i];
        }
    }
    return color_graph;
}

std::vector<uint32_t> Graph::FindCicle() {
    
}

bool Graph::CheckPlanar () {
    DeleteBridges();
    std::vector<uint32_t> color;
    uint32_t color_num = ColorGraph(&color);
    for (size_t i = 1; i < color.size(); ++i) {
        std::cout << i << ": " << color[i] << std::endl;
    }
    for (size_t i = 1; i <= color_num; ++i) {
        Graph cur = GetColorGraph(i, color);
        cur.PrintGraph();                                   /**/
        std::vector<std::vector<uint32_t>> edges;

    }
    return true;
}