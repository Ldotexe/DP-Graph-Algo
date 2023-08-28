#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class Graph {
    public:
    size_t n;
    std::unordered_map<std::string, size_t> dictionary;
    std::vector<std::vector<size_t>> list;
    Graph(size_t n_);
    size_t FindDif (std::string& first, std::string& second);
    void FillGraph();
    void PrintGraph();
    void GetRequests ();
    ssize_t FindCarrol (size_t src, size_t dst);

};

int main () {
    size_t n;
    std::cin >> n;
    Graph g(n);
    g.FillGraph ();
    g.GetRequests ();
    return 0;
}

Graph::Graph(size_t n_) {
    n = n_;
    list.resize(n);
}

size_t Graph::FindDif (std::string& first, std::string& second) {
    size_t result = 0;
    for (size_t i = 0; i < first.size(); ++i) {
        result += (first[i] != second[i]);
    }
    return result;
}

void Graph::FillGraph() {
    std::vector<std::string> words;
    words.resize(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> words[i];
        dictionary[words[i]] = i;
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (FindDif(words[i], words[j]) == 1) {
                list[i].push_back(j);
                list[j].push_back(i);
            }
        }
    }
}

void Graph::PrintGraph() {
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << i << ": ";
        for (size_t j = 0; j < list[i].size(); ++j) {
            std::cout << list[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::GetRequests () {
    size_t m;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i) {
        std::string src, dst;
        std::cin >> src >> dst;
        std::cout << FindCarrol(dictionary[src], dictionary[dst]) << std::endl;
    }
}

ssize_t Graph::FindCarrol (size_t src, size_t dst) {
    std::vector<size_t> distance_src;
    std::vector<size_t> distance_dst;
    distance_src.resize(n); 
    distance_dst.resize(n);
    std::queue<size_t> bfs_src; 
    std::queue<size_t> bfs_dst;
    distance_src[src] = 0; 
    distance_dst[dst] = 0;
    bfs_src.push (src); 
    bfs_dst.push (dst);
    std::vector<bool> passed_src;
    std::vector<bool> passed_dst;
    passed_src.resize(n);
    passed_dst.resize(n);
    passed_src[src] = true;
    passed_dst[dst] = true;
    while (!bfs_src.empty() && !bfs_dst.empty()) {
        size_t cur_src = bfs_src.front();
        size_t cur_dst = bfs_dst.front();
        if (distance_dst[cur_dst] >= distance_src[cur_src]) {
            bfs_src.pop ();
            if (passed_dst[cur_src] == true) {
                return distance_dst[cur_src] + distance_src[cur_src];
            }
            for (size_t adjacent : list[cur_src]) {
                if (passed_src[adjacent] == false) {
                    bfs_src.push(adjacent);
                    passed_src[adjacent] = true;
                    distance_src[adjacent] = distance_src[cur_src] + 1;
                }
                if (passed_dst[adjacent] == true) {
                    return distance_dst[adjacent] + distance_src[adjacent];
                }
            }
        }
        else {
            bfs_dst.pop ();
            if (passed_src[cur_dst] == true) {
                return distance_src[cur_dst] + distance_dst[cur_dst];
            }
            for (size_t adjacent : list[cur_dst]) {
                if (passed_dst[adjacent] == false) {
                    bfs_dst.push(adjacent);
                    passed_dst[adjacent] = true;
                    distance_dst[adjacent] = distance_dst[cur_dst] + 1;
                }
                if (passed_src[adjacent] == true) {
                    return distance_dst[adjacent] + distance_src[adjacent];
                }
            }
        }
    }
    return -1;
}