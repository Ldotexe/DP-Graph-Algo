#include <cstdlib>
#include <iostream>

long double FindProbability (int n, int m);
long double FindProbability (int n, int m, int array_base, long double* cash_array);

int main () {
    int n, m;
    std::cin >> n >> m;
    std::cout.precision(10);
    long double probability = FindProbability(n, m);
    std::cout << probability / 6 << std::endl;
    return 0;
}

long double FindProbability (int n, int m) {
    long double *cash_array = new long double[n * m + 1];
    for (size_t i = 0; i <= n * m; ++i) {
        cash_array[i] = 3;
    }
    long double answer = FindProbability(n, m, m, cash_array);
    delete[] cash_array;
    return answer;
}

long double FindProbability (int n, int m, int array_base, long double *cash_array) {
    long double answer = 0.0;
    if (n == 1 && m <= 6 && m >= 1) {
        answer = 1;
        return answer;
    }
    if (m <= 0 || n == 1) {
        return 0;
    }
    if (cash_array[(n - 1) * array_base + m - 1] < 2){
        return cash_array[(n - 1) * array_base + m - 1];
    }
    for (size_t i = 1; i <= 6; ++i) {
        answer += FindProbability (n - 1, m - i, array_base, cash_array);
    }
    cash_array[(n - 1) * array_base + m - 1] = answer / 6;
    return answer / 6;
}