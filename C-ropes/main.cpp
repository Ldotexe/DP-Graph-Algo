#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>

int CountRopes (int n, int* nails_coordinates);
int CountRopes (int n, int* nails_coordinates, int value, int* cash_array);
void ReadArray (std::istream &is, size_t n, int* array);

int main () {
    size_t n;
    std::cin >> n;
    int* nails_coordinates = new int[n];
    ReadArray(std::cin, n, nails_coordinates);
    std::cout << CountRopes(n, nails_coordinates) << std::endl;
    delete [] nails_coordinates;
    return 0;
}

int CountRopes (int n, int* nails_coordinates) {
    if (nails_coordinates == nullptr){
        return 0;
    }
    std::sort(nails_coordinates, nails_coordinates + n);
    int* cash_array = new int[n + 1];
    cash_array[2] = nails_coordinates[1] - nails_coordinates[0];
    cash_array[3] = nails_coordinates[2] - nails_coordinates[0];
    int answer = CountRopes(n, nails_coordinates, n, cash_array);
    delete[] cash_array;
    return answer;
}

int CountRopes (int n, int* nails_coordinates, int value, int* cash_array){
    if (cash_array[value] != 0) {
        return cash_array[value];
    }
    cash_array[value] = std::min(CountRopes(n, nails_coordinates, value - 1, cash_array) + nails_coordinates[value - 1] - nails_coordinates[value - 2], CountRopes(n, nails_coordinates, value - 2, cash_array) + nails_coordinates[value - 1] - nails_coordinates[value - 2]);      
    return cash_array[value];
}

void ReadArray (std::istream &is, size_t n, int* array) {
    if (array == nullptr) {
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        is >> array[i];
    }
}

