#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

uint64_t CountPalindromes (std::string str, int length);
bool IsPalindrom  (std::string);
uint64_t CountPalindromes (std::string str);
bool check_num_in_array(std::vector<int> vec, int num);

int main () {
    std::string str;
    getline(std::cin, str);
    std::cout << CountPalindromes(str, str.size()) << std::endl;
    std::cout << CountPalindromes(str) << std::endl;
    return 0;
}

uint64_t CountPalindromes (std::string str, int length) {
    if (str.length() == 1) {
        return 1;
    }
    if (length == 0) {
        if (str.size() == 0) {
            return 0;
        }
        return IsPalindrom(str);
    }
    uint64_t answer = IsPalindrom(str);
    std::string str1, str2;
    for (size_t i = 0; i < length; i++) {
        str1 = str.substr(0, i) + str.substr(i + 1, str.size() - i - 1);
        answer += CountPalindromes(str1, i);
    }
    return answer;
}

bool IsPalindrom (std::string str) {
    int len = str.length();
    for (size_t i = 0; i < len / 2 + 1; i++) {
        if (str[i] != str[len - i - 1]){
            return false;
        }
    }
    return true;
}

uint64_t CountPalindromes (std::string str) {
    std::vector<int>* info = new std::vector<int>[str.size()];

    for (size_t i = 0; i < str.size(); ++i) {
        info[i].push_back(i);
        for (size_t j = 0; j < i; ++j)  {
            if (str[j] == str[i]) {
                if (check_num_in_array(info[i - 1], j + 1) || j == i -1) {
                    info[i].push_back(j);
                }
            }
        }
    }
    uint64_t answer = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        std::cout << i << " " << info[i].size() << std::endl;
        answer += info[i].size();
    }
    return answer;
}

bool check_num_in_array(std::vector<int> vec, int num){
    for (size_t i = 0; i < vec.size(); ++i) {
        if (num == vec[i]) {
            return true;
        }
    }
    return false;
}

