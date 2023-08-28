#include <iostream>
#include <inttypes.h>
#include <vector>
#include <queue>

class Graph {
    public:
    size_t n;
    size_t k;
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> list;
    std::queue<uint32_t> actions;
    int32_t* time;
    uint32_t* fires;
    uint32_t st;
    uint32_t fn;
    
    Graph(size_t n_, size_t k_);
    ~Graph();
    void FillGraph(size_t m);
    
    int64_t CountFireTime ();
    int64_t CountSpelTime ();
    int64_t GetResult ();
};

int main () {
    size_t n, m, k;
    std::cin >> n >> m >> k;
    Graph g(n, k);
    g.FillGraph(m);
    std::cout << g.GetResult() << std::endl;
    return 0;
}

Graph::Graph(size_t n_, size_t k_) {
    n = n_;
    k = k_;
    time = new int32_t[n];
    fires = new uint32_t[k];
}

Graph::~Graph() {
    delete[] time;
}

void Graph::FillGraph(size_t m) {
    list.resize(n);
    for (size_t i = 0; i < k; ++i) {
        std::cin >> fires[i];
        --fires[i];
    }
    uint32_t s, d, w;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> s >> d >> w;
        --s; --d;
        list[s].push_back(std::make_pair(d, w));
        list[d].push_back(std::make_pair(s, w));
    }
    std::cin >> st >> fn;
    --st; --fn;
}

int64_t Graph::CountFireTime() {
    for (size_t i = 0; i < n; ++i) {
        time[i] = -1;
    }
    for (size_t i = 0; i < k; ++i) {
        actions.push(fires[i]);
        time[fires[i]] = 0;
        int32_t cur;
        while (!actions.empty()) {
            cur = actions.front();
            actions.pop();
            for (auto ver : list[cur]) {
                if (time[ver.first] == -1 || time[ver.first] > time[cur] + ver.second) {
                    time[ver.first] = time[cur] + ver.second;
                    actions.push(ver.first);
                }
            }
        }
    }

    return time[fn];
}

int64_t Graph::CountSpelTime() {
    for (size_t i = 0; i < n; ++i) {
        time[i] = -1;
    }
    actions.push(st);
    time[st] = 0;
    int32_t cur;
    while (!actions.empty()) {
        cur = actions.front();
        actions.pop();
        for (auto ver : list[cur]) {
            if (time[ver.first] == -1 || time[ver.first] > time[cur] + ver.second) {
                time[ver.first] = time[cur] + ver.second;
                actions.push(ver.first);
            }
        }
    }

    return time[fn];
}

int64_t Graph::GetResult () {
    int64_t fire = CountFireTime();
    int64_t spel = CountSpelTime();
    if (fire > spel || fire == -1) {
        return spel;
    }
    return -1;
}