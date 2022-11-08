#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <type_traits>

typedef class invertible_amount {
public:
    int bills_number;
    int difference;
}invertible_amount;

invertible_amount* MoneyWithdraw(int m, int n, int* denomination_array);
int                MoneyWithdraw(int m, int n, int* denomination_array, invertible_amount* cash_array);
void PrintChange (int m, invertible_amount* cash_array);

int main() {
    int n, m;
    std::cin >> n;
    int *denomination_array = new int[n];
    if (denomination_array == nullptr) {
        return 0;
    }
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", denomination_array + i);
    }
    std::cin >> m;
    invertible_amount* cash_array = MoneyWithdraw(m, n, denomination_array);
    PrintChange (m, cash_array);
    delete[] denomination_array;
    delete[] cash_array;
    return 0;
}

invertible_amount* MoneyWithdraw(int m, int n, int* denomination_array) {
    invertible_amount* cash_array = new invertible_amount[m+1];
    if (cash_array == nullptr) {
        return 0;
    }
    std::sort(denomination_array, denomination_array + n);
    MoneyWithdraw(m, n, denomination_array, cash_array);
    return cash_array;
}


int MoneyWithdraw(int m, int n, int* denomination_array, invertible_amount* cash_array) {
    if (cash_array[m].bills_number != 0 || m == 0) {
        return cash_array[m].bills_number;
    }
    for (int i = 0; i < n && denomination_array[i] <= m; ++i) {
        int money_withdraw_result = MoneyWithdraw(m - denomination_array[i], n, denomination_array, cash_array);
        if (cash_array[m].bills_number == 0 || cash_array[m].bills_number > money_withdraw_result + 1 && money_withdraw_result != -1){
            cash_array[m].bills_number = MoneyWithdraw(m - denomination_array[i], n, denomination_array, cash_array) + 1;
            cash_array[m].difference = denomination_array[i];
        }
    }
    if (cash_array[m].bills_number == 0 && m != 0) {
        cash_array[m].bills_number = -1;
    }
    return cash_array[m].bills_number;
}

void PrintChange (int m, invertible_amount* cash_array){
    if (m == 0){
        std::cout << 0 << std::endl;
        return;
    }
    if (cash_array[m].bills_number == -1){
        std::cout << -1 << std::endl;
        return;
    }
    std::cout << cash_array[m].bills_number << std::endl;
    while (cash_array[m].difference != 0){
        std::cout << cash_array[m].difference << " ";
        m -= cash_array[m].difference;
    }
    std::cout << std::endl;
}