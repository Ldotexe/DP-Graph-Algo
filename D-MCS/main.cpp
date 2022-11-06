#include <algorithm>
#include <cstdlib>
#include <iostream>

struct MCS_Cash
{
    int* cash_array;
    size_t size;
    size_t place;
};

std::string MCS (std::string str1, std::string str2);

int main () {
    std::string str1 = "", str2 = "";
    getline(std::cin, str1);
    getline(std::cin, str2);
    std::cout << MCS(str1, str2) << std::endl;
    return 0;
}

std::string MCS (std::string str1, std::string str2){
    MCS_Cash cash;
    if (str1.size() == 0) {
        return "";
    }
    size_t array_base = str2.size() + 1;
    cash.cash_array = new int[2 * array_base + 100];
    cash.size = 0;
    cash.place = 0;
    for (size_t i = 0; i < str1.size() + 1; ++i) {
        for (size_t j = 0; j < str2.size() + 1; ++j) {
            if (i == 0 || j == 0){
                cash.cash_array[(i % 2) * array_base + j] = 0;
            }
            else{
                if (str1[i - 1] == str2[j - 1]) {
                    cash.cash_array[(i % 2) * array_base + j] = cash.cash_array[((i - 1) % 2) * array_base + (j - 1)] + 1;
                    if (cash.cash_array[(i % 2)* array_base + j] == cash.size) {
                        if (str1[i - cash.size] < str1[cash.place / array_base - cash.size]){
                            cash.place = i * array_base + j;
                        }
                    }
                    if (cash.cash_array[(i % 2) * array_base + j] > cash.size) {
                        cash.size = cash.cash_array[(i % 2) * array_base + j];
                        cash.place = i * array_base + j;
                    }

                }
                else{
                    cash.cash_array[(i % 2) * array_base + j] = 0;
                }
            }
        }
    }
    std::string answer = str1.substr(cash.place / array_base - cash.size, cash.size);
    delete[] cash.cash_array;
    return answer;

}