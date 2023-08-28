#include <algorithm>
#include <iostream>
#include <vector>
#include <inttypes.h>

class Graph {
    public:
    uint32_t n;
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> list;

    Graph(uint32_t n_);
    void FillGraph(uint32_t m);
    uint64_t GetMST ();
};

int main () {
    uint32_t n, m;
    std::cin >> n >> m;
    Graph g(n);
    g.FillGraph(m);
    std::cout << g.GetMST() << std::endl;
    return 0;
}

bool pair_sec_comp (std::pair<uint32_t, uint32_t> first, std::pair<uint32_t, uint32_t> second) {
    return first.second < second.second;
}

Graph::Graph(uint32_t n_) {
    n = n_;
    list.resize(n);
}

void Graph::FillGraph(uint32_t m) {
    uint32_t s, f, w;
    for (uint32_t i = 0; i < m; ++i) {
        std::cin >> s >> f >> w;
        s--; f--;
        list[s].push_back(std::make_pair(f, w));
        list[f].push_back(std::make_pair(s, w));
    }
}

uint64_t Graph::GetMST () {
    std::vector<uint32_t> MST;
    uint64_t answer = 0;
    std::vector<bool> in_tree;
    in_tree.resize(n);
    MST.push_back(0);
    in_tree[0] = true;
    std::pair<uint32_t, uint32_t> min_w;
    bool cur_min = false;
    for (uint32_t i = 0; i < n; ++i) {
        std::sort(list[i].begin(), list[i].end(), pair_sec_comp);
    }
    while (MST.size() < n) {
        cur_min = false;
        for (uint32_t ver : MST) {
            for (std::pair<uint32_t, uint32_t> adjacent : list[ver]) {
                if (in_tree[adjacent.first] == false) {
                    if (min_w.second > adjacent.second || cur_min == false) {
                        cur_min = true;
                        min_w = adjacent;
                    }
                    break;
                }
            }
        }
        MST.push_back(min_w.first);
        in_tree[min_w.first] = true;
        answer += min_w.second;
    }

    return answer;
}