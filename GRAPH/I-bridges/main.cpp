#include <iostream>
#include <set>
#include <vector>

struct DfsStruct {
    std::vector<size_t> tin, ret;
    std::vector<bool> color;
    size_t time;
};

class Graph {
    public:
    std::vector<std::vector<std::pair<size_t, size_t>>> list;
    DfsStruct dfs;
    void FillGraph (size_t n, size_t m);
    void DfsBridge (size_t parent, size_t vertex, std::set<size_t>& bridges);
    std::set<size_t> Findbridges ();
};

template <typename T>
std::ostream& operator<< (std::ostream& os, std::set<T> set) {
    os << set.size() << std::endl;
    for (auto elem : set) {
        os << elem << " ";
    }
    os << std::endl;
    return os;
}  


int main () {
    Graph g;
    size_t n, m;
    std::cin >> n >> m;
    g.FillGraph (n, m); 
    std::cout << g.Findbridges(); 
    return 0;
}

void Graph::FillGraph (size_t n, size_t m) {
    list.resize (n + 1);
    dfs.color.resize (n + 1);
    dfs.tin.resize (n + 1);
    dfs.ret.resize (n + 1);
    size_t v1, v2;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> v1 >> v2;
        std::pair<size_t, size_t> path_with_number = std::make_pair (v2, i + 1);
        list[v1].push_back (path_with_number);
        path_with_number.first = v1;
        list[v2].push_back (path_with_number);
    }
    for (size_t i = 0; i < n + 1; ++i) {
        dfs.color[i] = 0;
    }
}

std::set<size_t> Graph::Findbridges () {
    std::set<size_t> answer;
    dfs.time = 0;
    for (size_t i = 1; i < list.size(); ++i) {
        if (dfs.color[i] == 0) {
            DfsBridge (0, i, answer);
        }
    }
    return answer;
}

void Graph::DfsBridge (size_t parent, size_t vertex, std::set<size_t>& bridges) {
    dfs.color[vertex] = 1;
    ++dfs.time;
    dfs.tin[vertex] = dfs.time;
    dfs.ret[vertex] = dfs.time;

    for (auto adjacent_vertex : list[vertex]) {
        if (adjacent_vertex.first == parent) {
            continue;
        }
        if (dfs.color[adjacent_vertex.first] == 0) {
            DfsBridge (vertex, adjacent_vertex.first, bridges);
            dfs.ret[vertex] = std::min (dfs.ret[vertex], dfs.ret[adjacent_vertex.first]);

            if (dfs.tin[vertex] < dfs.ret[adjacent_vertex.first]) {
                bridges.insert (adjacent_vertex.second);
            }
        }
        else {
            dfs.ret[vertex] = std::min (dfs.ret[vertex], dfs.tin[adjacent_vertex.first]);
        }
    }
}