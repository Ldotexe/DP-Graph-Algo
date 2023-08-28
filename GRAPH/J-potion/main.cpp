#include <iostream>
#include <vector>
#include <stack>

class BrewingStand {
    public:

    size_t big_potion_capacity_;
    size_t small_potion1_capacity_;
    size_t small_potion2_capacity_;
    size_t destination_potion_;
    size_t potion_capacity_[3];
    size_t potion_condition[3];
    std::stack<std::pair<size_t, size_t>> actions;
    std::vector<std::vector<size_t>> complexity_of_actions_;

    BrewingStand ();
    void StartBewing (size_t big_potion_capacity, size_t small_potion1_capacity, size_t small_potion2_capacity, size_t destination_bi_potion, std::vector<std::vector<size_t>> complexity_of_actions);
    size_t GetAmountOfActions ();
};



int main () {
    BrewingStand bst;
    size_t N, M, K, L;
    std::cin >> N >> M >> K >> L;

    std::vector<std::vector<size_t>> complexity_of_actions (M + 1);
    for (size_t i = 0; i < M + 1; ++i) {
        complexity_of_actions[i] = std::vector<size_t> (K + 1);
    }
    
    bst.StartBewing(N, M, K, L, complexity_of_actions);
    ssize_t answer = bst.GetAmountOfActions();
    if (answer == 0) {
        std::cout << "OOPS" << std::endl;
    }
    else {
        std::cout << answer << std::endl;
    }
    return 0;
}

BrewingStand::BrewingStand(){}

void BrewingStand::StartBewing (size_t big_potion_capacity, size_t small_potion1_capacity, size_t small_potion2_capacity, size_t destination_bi_potion, std::vector<std::vector<size_t>> complexity_of_actions) {
    big_potion_capacity_ = big_potion_capacity;
    small_potion1_capacity_ = small_potion1_capacity;
    small_potion2_capacity_ = small_potion2_capacity;
    destination_potion_ = destination_bi_potion;
    complexity_of_actions_ = complexity_of_actions;
}

size_t BrewingStand::GetAmountOfActions () {
    std::pair<size_t, size_t> current = std::make_pair(0, 0);
    actions.push (current);

    potion_capacity_[0] = big_potion_capacity_;
    potion_capacity_[1] = small_potion1_capacity_;
    potion_capacity_[2] = small_potion2_capacity_;

    while (!actions.empty ()) {
        current = actions.top();
        actions.pop();

        potion_condition[0] = big_potion_capacity_ - current.first - current.second;
        potion_condition[1] = current.first;
        potion_condition[2] = current.second;

        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) { // from i to j
                if (i != j) {
                    size_t ammount = std::min (potion_condition[i], potion_capacity_[j] - potion_condition[j]);
                    potion_condition[i] -= ammount;
                    potion_condition[j] += ammount;
                    size_t p1 = potion_condition[1], p2 = potion_condition[2];
                    if (complexity_of_actions_[p1][p2] > complexity_of_actions_[current.first][current.second] + 1 || (complexity_of_actions_[p1][p2] == 0 && (p1 != 0 || p2 != 0))) {
                        complexity_of_actions_[p1][p2] = complexity_of_actions_[current.first][current.second] + 1;
                        actions.push (std::make_pair (p1, p2));
                    }
                    
                    // back
                    potion_condition[i] += ammount;
                    potion_condition[j] -= ammount;
                }
            }
        }
    }

    size_t answer = 0;
    for (size_t p1 = 0; p1 <= small_potion1_capacity_ && p1 <= big_potion_capacity_ - destination_potion_; ++p1) {
        size_t p2 = big_potion_capacity_ - destination_potion_ - p1;
        if (p2 <= small_potion2_capacity_) {
            if (complexity_of_actions_[p1][p2] != 0){
                if (answer == 0) {
                    answer = complexity_of_actions_[p1][p2];
                }
                else {
                    answer = std::min(answer, complexity_of_actions_[p1][p2]);
                }
            }
        }
    }

    return answer;
}

