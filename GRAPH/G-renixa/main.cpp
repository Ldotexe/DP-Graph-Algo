#include <iostream>
#include <string>
#include <stack>
#include <vector>

struct LexVertex {
    std::vector<char> edges;
    char num_edges_in;
};

class LexGraph {
    public:
    std::vector<LexVertex> list;
    void FillLex (size_t n, size_t m);
    void PrintLex ();
    char* FindCipher ();
};

int main () {
    LexGraph g;
    size_t n, m;
    std::cin >> n >> m;
    g.FillLex (n, m);
    char* answer = g.FindCipher();
    std::cout << answer << std::endl;
    delete[] answer;
    return 0;
}

void LexGraph::FillLex (size_t n, size_t m) {
    list.resize(n);
    std::string word1, word2;
    std::cin >> word2;
    for (size_t i = 1; i < m; ++i) {
        word1 = word2;
        std::cin >> word2;
        for (size_t j = 0; j < word1.size() && j < word2.size(); ++j) {
            if (word1[j] != word2[j]) {
                int check = 0;
                for (size_t k = 0; k < list[word1[j] - 'A'].edges.size(); ++k) {
                    if (list[word1[j] - 'A'].edges[k] == word2[j] - 'A') {
                        check = 1;
                    }
                }
                if (check != 1){
                    list[word1[j] - 'A'].edges.push_back (word2[j] - 'A');
                    list[word2[j] - 'A'].num_edges_in++;
                }
                break;
            }
        }
    }
}

char* LexGraph::FindCipher () {
    char* answer = new char[list.size()];
    char* numbers = new char[list.size()];
    std::stack<char> dfs;
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i].num_edges_in == 0) {
            dfs.push (i);
            numbers[dfs.top()] = 0;
        }
    }
    while (!dfs.empty()) {
        char current = dfs.top();
        dfs.pop();
        for (size_t i = 0; i < list[current].edges.size(); ++i) {
            numbers[list[current].edges[i]] = numbers[current] + 1;
            dfs.push(list[current].edges[i]);
        }
    }
    
    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t j = 0; j < list.size(); ++j) {
            if (i == numbers[j]) {
                answer[i] = j + 'A';
            }
        }
    }
    delete[] numbers;
    return answer;
}