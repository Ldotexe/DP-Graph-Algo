#include <cstdlib>
#include <iostream>

struct TableInfo {
    int x;
    int y;
    int array_base;
};

char GameResult (int x, int y);
void FullWinGame (int x, int y, TableInfo info, char* cash_array);
int FindZero (TableInfo info, char* cash_array);

int main () {
    int x, y;
    std::cin >> x >> y;
    std::cout << (GameResult(x, y) == '1' ? "F" : "S") << std::endl;
    return 0;
}

char GameResult (int x, int y) {
    TableInfo info {x, y, y};
    char* cash_array = new char[x * y];
    for (size_t i = 0; i < x; ++i){
        for (size_t j = 0; j < y; ++j){
            cash_array[i * info.array_base + j] = '0';
        }
    }
    FullWinGame (x, y, info, cash_array);
    char answer = cash_array[0];
    delete[] cash_array;
    return answer;
}

void FullWinGame (int x, int y, TableInfo info, char* cash_array){
    if (x == 0 || y == 0) {
        return;
    }
    cash_array[(x - 1) * info.array_base + y - 1] = '2';
    for (size_t i = 0; i < x - 1; ++i){
        cash_array[i * info.array_base + y - 1] = '1';
    }
    for (size_t i = 0; i < y - 1; ++i){
        cash_array[(x - 1)* info.array_base + i] = '1';
    }
    for (size_t i = 2; x >= i && y >= i; ++i) {
        cash_array[(x - i) * info.array_base + y - i] = '1';
    }
    int coordinates = FindZero(info, cash_array);
    if (coordinates == 0) {
        return;
    }
    FullWinGame (coordinates / info.array_base, coordinates % info.array_base, info, cash_array); 
}

int FindZero (TableInfo info, char *cash_array) {
    for (ssize_t i = info.x - 1; i >= 0; --i) {
        for (ssize_t j = info.y - 1; j >= 0; --j){
            if (cash_array[i * info.array_base + j] == '0') {
                return (i + 1) * info.array_base + (j + 1);
            }
        }
    }
    return 0;
}