#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>

uint64_t GrasshopperVariants(int n, int m);
uint64_t GrasshopperVariants(int n, int m, uint64_t *cash_array);

int main(){
    int n, m;
    std::cin >> n >> m;
    std::cout << GrasshopperVariants(n, m) << std::endl;
    return 0;
}

uint64_t GrasshopperVariants(int n, int m){
    uint64_t *cash_array = new uint64_t[n + 1];
    if (cash_array == nullptr){
        return 0;
    }
    cash_array[0] = 1;
    uint64_t answer = GrasshopperVariants(n, m, cash_array);
    delete[] cash_array;
    return answer;
}

uint64_t GrasshopperVariants(int n, int m, uint64_t *cash_array){
    if (n < 0){
        return 0;
    }
    if (cash_array[n] != 0){
        return cash_array[n];
    }
    for (size_t i = 1; i <= m; ++i){
        cash_array[n] += GrasshopperVariants(n - i, m, cash_array);
    }
    return cash_array[n];
}
