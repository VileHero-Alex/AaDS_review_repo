#include <iostream>
#include <vector>
#include <set>

#define int long long 

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

struct Edge {
  int to, weight;
};

class Graph {
 private:
  int n_, m_;
  int res_ = 0;
  std::vector<std::vector<Edge>> graph_;

 public:
  void ReadData() {
    std::cin >> n_ >> m_;
    graph_.resize(n_);
    for (int i = 0; i < m_; ++i) {
      int u, v, w;
      std::cin >> u >> v >> w;
      --u, --v;
      graph_[u].push_back({v, w});
      graph_[v].push_back({u, w});
    }
  }

  void FindMST() {
    std::set<std::pair<int, int>> pool;
    std::vector<int> used(n_, 0);
    for (auto [to, weight] : graph_[0]) {
      pool.insert({weight, to});
    }
    used[0] = 1;

    while (!pool.empty()) {
      int cur = (*pool.begin()).second;
      int ed = (*pool.begin()).first;
      pool.erase(pool.begin());
      if (used[cur] == 0) {
        res_ += ed;
      }
      used[cur] = 1;
      for (auto [to, weight] : graph_[cur]) {
        if (!used[to]) {
          pool.insert({weight, to});
        }
      }
    }
  }

  void PrintWeightOfMST() {
    std::cout << res_ << "\n";
  }
};

void Solve() {
  Graph my_graph;
  my_graph.ReadData();
  my_graph.FindMST();
  my_graph.PrintWeightOfMST();
}

signed main() {
  SpeedUp();
  Solve();
}
