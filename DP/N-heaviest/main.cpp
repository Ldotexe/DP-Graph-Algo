#include <iostream>
#include <inttypes.h>

int64_t FindHeaviest (int64_t* matrix, size_t n, size_t m) {
    int64_t ans;
    int64_t cur;
    bool ans_check = false;
    for (size_t i = 1; i < n + 1; i++) {
        for (size_t j = 1; j < m + 1; j++) {
            matrix[i * m + j] += matrix[(i - 1) * m + j] + matrix[i * m + j - 1] - matrix[(i - 1) * m + j - 1];
        }
    }
    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t j = 1; j < m + 1; ++j) {
            for (size_t k = 0; k < i; ++k) {
                for (size_t l = 0; l < j; ++l) {
                    cur = matrix[i * m + j] - matrix[k * m + j] - matrix[i * m + l] + matrix[k * m + l];
                    if (ans < cur || ans_check == false) {
                        ans_check = true;
                        ans = cur;
                    }
                }
            }
        }
    }
    return ans;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    int64_t* matrix = new int64_t[(n + 1) * (m + 1) + 1];
    for (size_t i = 0; i < n; ++i) {
        matrix[i * m] = 0;
    }
    for (size_t i = 0; i < m; ++i) {
        matrix[i] = 0;
    }
    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t j = 1; j < m + 1; ++j) {
            std::cin >> matrix[i * m + j];
        }
    }
    std::cout << FindHeaviest(matrix, n, m) << std::endl;

    delete[] matrix;
}