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
    std::vector<size_t> distance;
    std::vector<bool> passed;
    distance.resize(n);
    passed.resize(n);
    std::queue<size_t> bfs;
    distance[src] = 0;
    passed[src] = true;
    bfs.push (src);
    while (!bfs.empty()) {
        size_t cur = bfs.front();
        bfs.pop();
        for (size_t adjacent : list[cur]) {
            if (passed[adjacent] == false) {
                passed[adjacent] = true;
                distance[adjacent] = distance[cur] + 1;
                bfs.push(adjacent);
            }
            if (adjacent == dst) {
                return distance[dst];
            }
        }
    }
    return -1;
}