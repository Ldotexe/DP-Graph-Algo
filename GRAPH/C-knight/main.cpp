#include <iostream>
#include <stack>
#include <vector>

size_t AMMOUNT_OF_KNIGHT_MOVES = 8;

class Cell {
public:
    std::pair<int, int> prev;
    size_t moves_from_start;
    bool passed;

    Cell();
    ~Cell();
};

Cell::Cell() {
    passed = false;
}

Cell::~Cell() {
}


void FindPath (size_t size, std::pair<int, int> start, std::pair<int, int> end, const std::pair<int, int>* knight_moves);

int main () {
    size_t size, start_digit, end_digit;
    char start_latter, end_latter;
    const std::pair<int, int> knight_moves[8] = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1 , 2}, {-1, -2}, {-2, 1}, {-2, -1}}; 
    scanf ("%ld %c%ld %c%ld", &size, &start_latter, &start_digit, &end_latter, &end_digit);
    FindPath (size, {start_latter - 'A', start_digit - 1}, {end_latter - 'A', end_digit - 1}, knight_moves);

}

void FindPath (size_t size, std::pair<int, int> start, std::pair<int, int> end, const std::pair<int, int>* knight_moves) {
    Cell* field = new Cell[size * size];
    std::stack<std::pair<int, int>> dfs;
    dfs.push(start);
    field[start.first + start.second * size].moves_from_start = 0;
    field[start.first + start.second * size].passed = true;

    while (!dfs.empty()) {
        std::pair<int, int> current = dfs.top();
        dfs.pop();

        for (size_t i = 0; i < AMMOUNT_OF_KNIGHT_MOVES; i++) {
            std::pair<int, int> new_cord = {current.first + knight_moves[i].first, current.second + knight_moves[i].second};
            if (new_cord.first >= 0 && new_cord.second >= 0 && new_cord.first < size && new_cord.second < size) {
                if (field[current.first + current.second * size].moves_from_start + 1 < field[new_cord.first + new_cord.second * size].moves_from_start || !field[new_cord.first + new_cord.second * size].passed) {
                    field[new_cord.first + new_cord.second * size].moves_from_start = field[current.first + current.second * size].moves_from_start + 1;
                    field[new_cord.first + new_cord.second * size].passed = true;
                    field[new_cord.first + new_cord.second * size].prev = current;
                    dfs.push(new_cord);
                }
            }
        }
    }

    std::cout << field[end.first + end.second * size].moves_from_start << std::endl;

    for (std::pair<int, int> i = end; field[i.first + i.second * size].moves_from_start != 0; i = field[i.first + i.second * size].prev) {
        dfs.push(i);
    }
    for (std::pair<int, int> i = dfs.top(); !dfs.empty(); dfs.pop()) {
        i = dfs.top();
        std::cout << (char)(i.first + 'A') << i.second + 1 << std::endl;
    }
    std::cout << std::endl;
    delete[] field;
}