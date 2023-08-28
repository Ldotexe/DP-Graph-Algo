#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>

class GameState {
    public:
    std::unordered_map<size_t, size_t> actions_from_start;
    std::queue<size_t> actions;
    
    ssize_t GetActionsToWin (size_t start_pos);
};

size_t GetStartPos ();
size_t StatefromString (std::string position);
size_t NextAction (std::string position, size_t cell, size_t side);

int main () {
    GameState game;
    size_t start_pos = GetStartPos ();
    std::cout << game.GetActionsToWin (start_pos) << std::endl;
    return 0;
}


size_t GetStartPos () {
    std::string str;
    size_t answer = 0;
    size_t deg = 1e8;
    for (size_t i = 0; i < 3; ++i) {
        std::getline(std::cin, str);
        for (size_t j = 0; j < 3; ++j) {
            if (str[j] != ' ') {
                answer += deg * (str[j] - '0');
            }
            deg /= 10;
        }
    }
    return answer;
}

size_t StatefromString (std::string position) {
    size_t answer = 0;
    size_t deg = 1e8;
    for (size_t i = 0; i < 9; ++i) {
        answer += deg * (position[i] - '0');
        deg /= 10;
    }
    return answer;
}

size_t NextAction (std::string position, size_t cell, size_t side) {
    switch (side) {
    case 0:
        if (cell > 2) {
            std::swap(position[cell], position[cell - 3]);
            return StatefromString(position);
        }
        break;
    case 1:
        if (cell % 3 != 0) {
            std::swap(position[cell], position[cell - 1]);
            return StatefromString(position);
        }
        break;
    case 2:
        if (cell % 3 != 2) {
            std::swap(position[cell], position[cell + 1]);
            return StatefromString(position);
        }
        break;
    case 3:
        if (cell < 6) {
            std::swap(position[cell], position[cell + 3]);
            return StatefromString(position);
        }
        break;
    }
    return 0;
}

ssize_t GameState::GetActionsToWin (size_t start_pos) {
    actions.push(start_pos);
    size_t current;
    std::string cur_str;

    while (!actions.empty()) {
        current = actions.front();
        actions.pop();
        if (current > 100000000){
            cur_str = std::to_string(current);
        }
        else {
            cur_str = "0";
            cur_str += std::to_string(current);
        }

        for (size_t i = 0; i < cur_str.size(); ++i) {
            if (cur_str[i] == '0') {
                for (size_t j = 0; j < 4; ++j) {
                    size_t next_action = NextAction (cur_str, i, j);
                    if (next_action != 0 && next_action != start_pos) {
                        if (actions_from_start[next_action] == 0 || (actions_from_start[next_action] != 0 && actions_from_start[next_action] > actions_from_start[current] + 1)) {
                            actions_from_start[next_action] = actions_from_start[current] + 1;
                            actions.push(next_action);
                        }
                    }
                }
            }
        }
    }

    size_t answer = actions_from_start[123456780];
    if (start_pos != 123456780 && answer == 0) {
        return -1;
    }
    return answer;
}