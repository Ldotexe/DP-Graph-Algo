#include <iostream>
#include <vector>
#include <stack>

size_t count_rounds (size_t n, size_t m, char* matrix, std::stack<std::pair<size_t, size_t>> start_cords);

int main () {
    size_t n, m, k;
    std::stack<std::pair<size_t, size_t>> start_cords;
    std::cin >> n >> m >> k;
    char* matrix = new char[n * m + 1];
    std::pair<size_t, size_t> start_cord;
    for (size_t i = 0; i < k; ++i) {
        std::cin >> start_cord.second >> start_cord.first;
        start_cords.push (start_cord);
    }
    std::cout << count_rounds (n, m, matrix, start_cords) << std::endl;
    delete[] matrix;
    return 0;
}

size_t count_rounds (size_t n, size_t m, char* matrix, std::stack<std::pair<size_t, size_t>> start_cords) {
    size_t rounds_counter = 0;
    std::stack<std::pair<size_t, size_t>> dfs1, dfs2;
    for (;!start_cords.empty(); start_cords.pop()) {
        dfs1.push(start_cords.top());
        matrix[start_cords.top().first * n + start_cords.top().second] = 1;
    }
    while (!(dfs1.empty() && dfs2.empty())) {
        ++rounds_counter;
        while (!dfs1.empty()) {
            std::pair<size_t, size_t> current = dfs1.top();
            size_t current_cord = current.first * n + current.second;
            dfs1.pop();
            matrix[current.first * n + current.second] = 1;
            if (current.first > 0) {
                if (matrix[current_cord - n] == 0){
                    dfs2.push (std::make_pair(current.first - 1, current.second));
                    matrix[current_cord - n] = 1;
                }
            }
            if (current.second > 0) {
                if (matrix[current_cord - 1] == 0){
                    dfs2.push (std::make_pair(current.first, current.second - 1));
                    matrix[current_cord - 1] = 1;
                }
            }
            if (current.first < m - 1) {
                if (matrix[current_cord + n] == 0){
                    dfs2.push (std::make_pair(current.first + 1, current.second));
                    matrix[current_cord + n] = 1;
                }
            }
            if (current.second < n - 1) {
                if (matrix[current_cord + 1] == 0){
                    dfs2.push (std::make_pair(current.first, current.second + 1));
                    matrix[current_cord + 1] = 1;
                }
            }
        }
        if (!dfs2.empty()) {
            ++rounds_counter;
        }
        while (!dfs2.empty()) {
            std::pair<size_t, size_t> current = dfs2.top();
            size_t current_cord = current.first * n + current.second;
            dfs2.pop();
            matrix[current.first * n + current.second] = 1;
            if (current.first > 0) {
                if (matrix[current_cord - n] == 0){
                    dfs1.push (std::make_pair(current.first - 1, current.second));
                    matrix[current_cord - n] = 1;
                }
            }
            if (current.second > 0) {
                if (matrix[current_cord - 1] == 0){
                    dfs1.push (std::make_pair(current.first, current.second - 1));
                    matrix[current_cord - 1] = 1;
                }
            }
            if (current.first < m - 1) {
                if (matrix[current_cord + n] == 0){
                    dfs1.push (std::make_pair(current.first + 1, current.second));
                    matrix[current_cord + n] = 1;
                }
            }
            if (current.second < n - 1) {
                if (matrix[current_cord + 1] == 0){
                    dfs1.push (std::make_pair(current.first, current.second + 1));
                    matrix[current_cord + 1] = 1;
                }
            }
        }
    }
    return rounds_counter - 1;
}

/*
5 5 2
3 2
1 2
*/

/*
5 5 1
3 3 
*/

/*
3 2 2
0 1
1 1
*/

/*
4 1 2
0 1
0 2
*/