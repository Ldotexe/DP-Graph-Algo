#include <iostream>
#include <stack>

size_t count_carpets (size_t n, size_t m, char* matrix);

int main () {
    size_t n, m;
    std::cin >> n >> m;
    char* matrix = new char[n * m + 1];
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cin >> matrix[i * n + j];
        }
    }
    std::cout << count_carpets (n, m, matrix) << std::endl;
    delete[] matrix;
    return 0;
}

size_t count_carpets (size_t n, size_t m, char* matrix){
    size_t carpets = 0;
    std::stack<size_t> dfs;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (matrix[i * n + j] == '+'){
                dfs.push(i * n + j);
                ++carpets;
            }
            while (!dfs.empty()) {
                size_t current = dfs.top();
                size_t x = current / n;
                size_t y = current % n;
                matrix[current] = ' ';

                dfs.pop();
                
                if (x > 0) {
                    if (matrix[current - n] == '+'){
                        matrix[current - n] = ' ';
                        dfs.push(current - n);
                    }
                }
                if (y > 0) {
                    if (matrix[current - 1] == '+'){
                        matrix[current - 1] = ' ';
                        dfs.push(current - 1);
                    }
                }
                if (x < m - 1) {
                    if (matrix[current + n] == '+'){
                        matrix[current + n] = ' ';
                        dfs.push(current + n);
                    }
                }
                if (y < n - 1) {
                    if (matrix[current + 1] == '+'){
                        matrix[current + 1] = ' ';
                        dfs.push(current + 1);
                    }
                }

            }
        }
    }

    return carpets;
}