#include <iostream>
#include <vector>
#include <set>

using ll = long long;

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

struct Edge {
  ll to, weight;
};

struct EdgeCmp {
  bool operator()(const Edge& first, const Edge& second) const {
    if (first.weight != second.weight) {
      return first.weight < second.weight;
    }
    return first.to < second.to;
  }
};

class Graph {
 private:
  ll n_, m_;
  ll res_ = 0;
  std::vector<std::vector<Edge>> graph_;

 public:
  void ReadData() {
    std::cin >> n_ >> m_;
    graph_.resize(n_);
    for (ll i = 0; i < m_; ++i) {
      ll u, v, w;
      std::cin >> u >> v >> w;
      --u, --v;
      graph_[u].push_back({v, w});
      graph_[v].push_back({u, w});
    }
  }

  void FindMST() {
    std::set<Edge, EdgeCmp> pool;
    std::vector<ll> used(n_, 0);
    for (auto [to, weight] : graph_[0]) {
      pool.insert({to, weight});
    }
    used[0] = 1;

    while (!pool.empty()) {
      ll cur = (*pool.begin()).to;
      ll ed = (*pool.begin()).weight;
      pool.erase(pool.begin());
      if (used[cur] == 0) {
        res_ += ed;
      }
      used[cur] = 1;
      for (auto [to, weight] : graph_[cur]) {
        if (!used[to]) {
          pool.insert({to, weight});
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

int main() {
  SpeedUp();
  Solve();
}
