#include <iostream>
#include <vector>
#include <stack>

class Graph {
    public:
    std::vector<std::vector<size_t>> list;
    void GetGraph ();
    void FindComponents ();
};



int main () {
    Graph g;
    g.GetGraph ();
    g.FindComponents ();
    return 0;
}

void Graph::GetGraph () {
    size_t n, m;
    std::cin >> n >> m;
    list.resize(n + 1);
    size_t first, second;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> first >> second;
        list[first].push_back(second);
        list[second].push_back(first);
    }
}

void Graph::FindComponents () {
    std::stack<size_t> dfs;
    size_t* colors = new size_t[list.size()];
    size_t current_color = 0;
    for (size_t i = 1; i < list.size(); ++i) {
        if (colors[i] == 0) {
            dfs.push(i);
            ++current_color;
            while (!dfs.empty()) {
                size_t current = dfs.top();
                dfs.pop();
                if (colors[current] == 0) {
                    colors[current] = current_color;
                    for (size_t j = 0; j < list[current].size(); ++j) {
                        dfs.push(list[current][j]);
                    }
                }
            }
        }
    }

    std::cout << current_color << std::endl;

    for (size_t i = 1; i < list.size(); ++i) {
        std::cout << colors[i] << " ";
    }
    std::cout << std::endl;
    delete[] colors;
}