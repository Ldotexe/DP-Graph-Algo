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
    std::vector<std::vector<int>> list;
    DfsStruct dfs;
    void FillGraph (size_t n, size_t m);
    void DfsVertex (size_t parent, size_t vertex, std::set<size_t>& junctions);
    std::set<size_t> FindJunctions ();
};

void PrintSet_size_t (std::set<size_t>) {

}

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
    std::cout << g.FindJunctions(); 
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
        list[v1].push_back (v2);
        list[v2].push_back (v1);
    }
    for (size_t i = 0; i < n + 1; ++i) {
        dfs.color[i] = 0;
    }
}

std::set<size_t> Graph::FindJunctions (){
    std::set<size_t> answer;
    dfs.time = 0;
    for (size_t i = 1; i < list.size(); ++i) {
        if (dfs.color[i] == 0) {
            DfsVertex (0, i, answer);
        }
    }
    return answer;
}

void Graph::DfsVertex (size_t parent, size_t vertex, std::set<size_t>& junctions) {
    dfs.color[vertex] = 1;
    ++dfs.time;
    dfs.tin[vertex] = dfs.time;
    dfs.ret[vertex] = dfs.time;

    size_t children = 0;
    for (auto adjacent_vertex : list[vertex]) {
        if (adjacent_vertex == parent) {
            continue;
        }
        if (dfs.color[adjacent_vertex] == 0) {
            ++children;
            DfsVertex (vertex, adjacent_vertex, junctions);
            dfs.ret[vertex] = std::min (dfs.ret[vertex], dfs.ret[adjacent_vertex]);

            if (dfs.tin[vertex] <= dfs.ret[adjacent_vertex] && parent != 0) {
                junctions.insert (vertex);
            }
        }
        else {
            dfs.ret[vertex] = std::min (dfs.ret[vertex], dfs.tin[adjacent_vertex]);
        }
    }

    if (parent == 0 && children > 1) {
        junctions.insert (vertex);
    }
}