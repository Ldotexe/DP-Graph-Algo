#include <iostream>
#include <queue>

class Model {
    public:
    size_t n;
    size_t m;
    int* higth_matrix;
    int* energy_cost;
    std::queue<int> actions;

    Model (int n_, int m_);
    ~Model ();
    void GetMatrix ();
    int GetCost ();
};

int main () {
    size_t n, m;
    std::cin >> n >> m;
    Model g(n, m);
    g.GetMatrix();
    std::cout << g.GetCost() << std::endl;
    return 0;
}

Model::Model(int n_, int m_) {
    n = n_; m = m_;
    higth_matrix = new int[n * m + 1];
    energy_cost  = new int[n * m + 1];
}

Model::~Model() {
    delete []higth_matrix;
    delete []energy_cost;
}

void Model::GetMatrix() {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            std::cin >> higth_matrix[i * m + j];
            energy_cost[i * m + j] = -1;
        }
    }
}

int Model::GetCost() {
    energy_cost[0] = 0;
    actions.push (0);

    int x_act[4] = {1, -1, 0, 0}; 
    int y_act[4] = {0, 0, 1, -1};
    while (!actions.empty()) {
        int cur = actions.front();
        int cur_x = cur % m;
        int cur_y = cur / m;
        actions.pop();
        for (size_t i = 0; i < 4; ++i) {
            cur_x += x_act[i];
            cur_y += y_act[i];
            if (cur_x >= 0 && cur_x < m && cur_y >= 0 && cur_y < n) {
                int new_cur = cur_y * m + cur_x;
                int trans_cost = energy_cost[cur] + std::max(0, higth_matrix[new_cur] - higth_matrix[cur]);
                if (energy_cost[new_cur] == -1 || energy_cost[new_cur] > trans_cost) {
                    energy_cost[new_cur] = trans_cost;
                    actions.push(new_cur);
                }
            }
            cur_x -= x_act[i];
            cur_y -= y_act[i];
        }
    }

    return energy_cost[n * m - 1];
}

/*
3 5 
3 1 4 1 5 
9 2 6 5 3 
5 9 7 9 3
*/