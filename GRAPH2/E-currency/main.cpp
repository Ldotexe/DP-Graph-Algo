#include <iostream>
#include <vector>
#include <inttypes.h>
#include <queue>

class Economy {
    public:
    uint32_t n;
    uint32_t s;
    long double v;
    std::vector<std::vector<std::pair<uint32_t, std::pair<long double, long double>>>> list;
    std::vector<long double> wealth;
    
    Economy(uint32_t n_, uint32_t s_, long double v_);
    void FillEconomy(uint32_t m);
    bool CheckBusiness ();
};

int main () {
    uint32_t n, m, s;
    long double v;
    std::cin >> n >> m >> s >> v;
    Economy g(n, s, v);
    g.FillEconomy(m);
    std::cout << (g.CheckBusiness() == true ? "YES" : "NO") << std::endl;
    return 0;
}

Economy::Economy (uint32_t n_, uint32_t s_, long double v_) {
    n = n_;
    s = --s_;
    v = v_;
    list.resize(n);
    wealth.resize(n);
    wealth[s] = v;
}

void Economy::FillEconomy (uint32_t m) {
    uint32_t a, b;
    long double rab, cab, rba, cba;
    for (uint32_t i = 0; i < m; i++) {
        std::cin >> a >> b >> rab >> cab >> rba >> cba;
        --a; --b;
        list[a].push_back(std::make_pair(b, std::make_pair(rab, cab)));
        list[b].push_back(std::make_pair(a, std::make_pair(rba, cba)));
    }
}

bool Economy::CheckBusiness () {
    std::vector<bool> passed;
    passed.resize(n);
    std::queue<uint32_t> currency;
    uint32_t curr;
    currency.push(s);
    passed[s] = true;
    while (!currency.empty()) {
        curr = currency.front();
        currency.pop();
        for (auto change : list[curr]) {
            long double cur_res = (wealth[curr] - change.second.second) * change.second.first;
            if (wealth[change.first] < cur_res || passed[change.first] == false && cur_res > 0) {
                wealth[change.first] = cur_res;
                passed[change.first] = true;
                currency.push(change.first);
                if (wealth[s] > v) {
                    return true;
                }
            }
        }
    }

    return false;
}