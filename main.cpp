#include <iostream>

int CountSquares (int n);

int main () {
    int n;
    std::cin >> n;
    std::cout << CountSquares (n) << std::endl;
    return 0;
}

int CountSquares (int n) {
    int* cash_array = new int[n + 1];
    for (size_t i = 0; i <= n; i++) {
        for (size_t j = 1; i + j * j <= n; ++j){
            if (cash_array[i + j * j] != 0) {
                cash_array[i + j * j] = std::min (cash_array[i + j * j], cash_array[i] + 1);
            }
            else {
                cash_array[i + j * j] = cash_array[i] + 1;
            }
        }
    }
    int answer = cash_array[n];
    delete[] cash_array;
    return answer;
}