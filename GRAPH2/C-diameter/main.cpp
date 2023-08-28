#include <iostream>

class Graph {
    public:
    uint32_t n;
    int32_t* matrix;

    Graph(uint32_t n_);
    void FillGraph ();
    void MakePath ();
    uint32_t FindDiameter ();
};

int main () {
    uint32_t n;
    std::cin >> n;
    Graph g(n);
    g.FillGraph();
    g.MakePath();
    std::cout << g.FindDiameter() << std::endl;
}

Graph::Graph(uint32_t n_) {
     n = n_;
     matrix = new int32_t[n * n];
}

void Graph::FillGraph() {
    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            std::cin >> matrix[i * n + j];
        }
    }
}

void Graph::MakePath () {
    for (uint32_t short_cut = 0; short_cut < n; ++short_cut) {
        for (uint32_t first = 0; first < n; ++first) {
            for (uint32_t second = 0; second < n; ++second) {
                if (matrix[first * n + second] == -1) {
                    if (matrix[first * n + short_cut] != -1 && matrix[short_cut * n + second] != -1) {
                        matrix[first * n + second] = matrix[first * n + short_cut] + matrix[short_cut * n + second];
                    }
                }
                else {
                    if (matrix[first * n + short_cut] != -1 && matrix[short_cut * n + second] != -1) {
                        matrix[first * n + second] = std::min(matrix[first * n + short_cut] + matrix[short_cut * n + second], matrix[first * n + second]);
                    }
                }
            }
        }
    }
}

uint32_t Graph::FindDiameter () {
    int32_t result = 0;
    for (uint32_t first = 0; first < n; ++first) {
        for (uint32_t second = 0; second < n; ++second) {
            result = std::max (result, matrix[first * n + second]);
        }
    }

    return result;
}