#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>

size_t answer(std::vector<std::vector<ssize_t>>& psc, size_t N, size_t K) {
    for (size_t idx = 0; idx <= N; ++idx) {
        size_t curmax = 0;

        size_t bound = std::min(K, idx);
        for (ssize_t col = 0; col <= bound; ++col)
            curmax += psc[idx][col];

        if (curmax >= N) {
            return idx;
        }
    }
}

void build_triangle(std::vector<std::vector<ssize_t>>& psc, size_t N, size_t K) {
    for (size_t row = 1; row <= N; ++row) {
        for (size_t col = 1; col <= K; ++col) {
            psc[row][col] = psc[row - 1][col - 1] + psc[row - 1][col];
        }
    }
}

size_t mtlog(size_t n) {
    size_t ans = 0;
    for (;n > 0; n /= 1000) {
        ++ans;
    }   
    return ans;
}

int main() {
    size_t n = 0, k = 0;
    std::cin >> n >> k;

    if (k == 0) {
        return -1;
    }

    k = std::max(k, mtlog(n));

    std::vector<std::vector<ssize_t>> psc(n + 1, std::vector<ssize_t>(k + 1));
    for (size_t v_idx = 0; v_idx <= n; ++v_idx)
        ++psc[v_idx][0];

    build_triangle(psc, n, k);
    std::cout << answer(psc, n, k) << std::endl;
    return 0;
}