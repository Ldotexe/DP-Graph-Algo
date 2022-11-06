#include <cstdlib>
#include <iostream>

bool GameResult (int n);

int main () {
    int n;
    std::cin >> n;
    std::cout << (GameResult(n) ? "First" : "Second") << std::endl;
    return 0;
}

bool GameResult (int n) {
    char* cash_array = new char[n + 1];
    cash_array[1] = 1;
    int current_root = 1;
    for (int i = 2; i <= n; i += current_root + 1) {
        cash_array[i] = 0;
        if ((current_root + 1) * (current_root + 1) <= i + current_root + 1) {
            ++current_root;
        }
        for (int j = i + 1; j <= i + current_root && j <= n; ++j) {
            cash_array[j] = 1;
        }
    }
    bool answer = cash_array[n];
    delete[] cash_array;
    return answer;
}