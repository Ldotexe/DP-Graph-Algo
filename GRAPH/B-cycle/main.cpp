#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>

class Graph {
public:
    std::vector<std::vector<int>> list;
    std::vector<int> cycle;
    void GetGraph();
    void PrintGraph();
    ssize_t Cycle();
};

void FindCycle (Graph& g);

int main() {
    Graph g;
    g.GetGraph();
    FindCycle(g);
    return 0;
}

void Graph::GetGraph() {
    int n, m;
    std::cin >> n >> m;
    list.resize(n);
    cycle.resize(n);
    int first, second;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> first >> second;
        list[first - 1].push_back(second - 1);
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


void FindCycle (Graph& g) {
    ssize_t vertex = g.Cycle();
    std::vector<size_t> answer;
    if (vertex != -1) {
        std::cout << "YES" << std::endl;
        for (ssize_t i = g.cycle[vertex]; i != vertex; i = g.cycle[i]) {
             answer.push_back(i + 1);
        }
        answer.push_back(vertex + 1);
        for (ssize_t i = answer.size() - 1; i >= 0; --i) {
            std::cout << answer[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }
}

ssize_t Graph::Cycle() {
    std::stack<int> dfs;
    char color[list.size()];
    for (size_t i = 0; i < list.size(); ++i) {
        color[i] = 0;
    }

    for (size_t i = 0; i < list.size(); ++i) {
        if (color[i] == '2') {
            continue;
        }
        dfs.push(i);

        while (!dfs.empty()) {
            size_t vertex = dfs.top();
            dfs.pop();

            if (color[vertex] == '1') {
                color[vertex] = '2';
                continue;
            }
            dfs.push(vertex);
            color[vertex] = '1';
            for (size_t j = 0; j < list[vertex].size(); ++j) {
                if (color[list[vertex][j]] == 0) {
                    dfs.push(list[vertex][j]);
                    cycle[list[vertex][j]] = vertex;
                }
                if (color[list[vertex][j]] == '1') {
                    cycle[list[vertex][j]] = vertex;
                    return vertex;
                }
            }
        }
    }
    return -1;
}

/*
2 2
1 2
2 1
 */

/*
3 3
1 2
2 3
1 3
*/

/*
6 6
1 2
2 3
1 4
1 5
6 1
3 6
*/

/*
5 6
1 2
2 3
3 1
1 4 
4 5
5 1
*/