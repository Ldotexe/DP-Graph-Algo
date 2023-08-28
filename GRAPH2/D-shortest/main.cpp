#include <iostream>
#include <inttypes.h>
#include <vector>
#include <queue>

class Graph {
    public:
    uint32_t n, m, s;
    std::vector<std::vector<std::pair<uint32_t, int64_t>>> list;
    std::vector<bool> reachable;

    Graph(uint32_t n_, uint32_t m_, uint32_t s_);
    void FillGraph ();
    void FillReachable ();
    void ShowDistance ();
};

int main () {
    uint32_t n, m, s;
    std::cin >> n >> m >> s;
    Graph g(n, m, s);
    g.FillGraph();
    g.FillReachable();
    g.ShowDistance();
}

Graph::Graph(uint32_t n_, uint32_t m_, uint32_t s_) {
    n = n_;
    m = m_;
    s = s_;
    list.resize(n);
    reachable.resize(n);
}

void Graph::FillGraph () {
    uint32_t st, e;
    int64_t w;
    for (uint32_t i = 0; i < m; ++i) {
        std::cin >> st >> e >> w;
        list[st].push_back(std::make_pair(e, w));
    }
}

void Graph::FillReachable () {
    reachable[s] = true;
    std::queue<uint32_t> bfs;
    bfs.push(s);
    while (!bfs.empty()) {
        uint32_t curr = bfs.front();
        bfs.pop();
        for (std::pair<uint32_t, int64_t> adjacent : list[curr]) {
            uint32_t next = adjacent.first;
            if (reachable[next] == false) {
                reachable[next] = true;
                bfs.push(next);
            }
        }
    }
}

void Graph::ShowDistance () {
    bool check = false;
    std::vector<int64_t> distance;
    std::vector<uint32_t> passed;
    distance.resize(n); passed.resize(n, false);
    distance[s] = 0; passed[s] = true;
    for (uint32_t i = 0; i < n + 1; ++i) {
        check = false;
        for (uint32_t j = 0; j < n; ++j) {
            for (uint32_t k = 0; k < list[j].size(); ++k) {
                if (passed[j] == true) {
                    if (distance[list[j][k].first] > distance[j] + list[j][k].second || passed[list[j][k].first] == false) {
                        distance[list[j][k].first] = distance[j] + list[j][k].second;
                        passed[list[j][k].first] = true;
                        check = true;
                    }
                }
            }
        }
    }
    if (check == true) {
        std::cout << "IMPOSSIBLE" << std::endl;
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        if (reachable[i] == true) {
            std::cout << distance[i] << " ";
        }
        else {
            std::cout << "UNREACHABLE "; 
        }
    }
    std::cout << std::endl;
    return;
}