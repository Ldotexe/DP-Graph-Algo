#include <iostream>
#include <vector>

size_t find_max_sub(std::vector<std::vector<bool>> matrix, size_t n) {
	size_t answer = 0;
    std::vector<size_t> s1, s2;
	s1.resize(n);
    s2.resize(n);

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			size_t cur = matrix[i][j];
			if (cur) {
				if (j > 0) {
					cur = std::min(s1[j - 1], std::min(s2[j - 1], s2[j])) + 1;
				}
			}
			s1[j] = s2[j];
			s2[j] = cur;
			answer = std::max(answer, cur);
		}
	}
    return answer;
}

int main() {
	size_t n = 0;
	std::cin >> n;
    std::vector<std::vector<bool>> matrix;
    matrix.resize(n);
    bool cur;
	for (size_t i = 0; i < n; ++i) {
        matrix[i].resize(n);
		for (size_t j = 0; j < n; ++j) {
			std::cin >> cur;
            matrix[i][j] = cur;
		}
	}

	std::cout << find_max_sub(matrix, n) << std::endl;
	return 0;
}