#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

class Graph {
 private:
  int n_, m_, cnt_ = 1;
  std::vector<int> used_, order_, comp_;
  std::vector<std::vector<int>> graph_, transp_;

  void Dfs1(int v) {
    used_[v] = 1;
    for (auto u : graph_[v]) {
      if (used_[u] == 0) {
        Dfs1(u);
      }
    }
    order_.push_back(v);
  }

  void Dfs2(int v) {
    comp_[v] = cnt_;
    for (auto u : transp_[v]) {
      if (comp_[u] == 0) {
        Dfs2(u);
      }
    }
  }

 public:
  void Init() {
    std::cin >> n_ >> m_;
    graph_.resize(n_);
    transp_.resize(n_);
    used_.resize(n_);
    comp_.resize(n_);
    for (int i = 0; i < m_; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      graph_[u].push_back(v);
      transp_[v].push_back(u);
    }
  }

  void TopSort() {
    for (int i = 0; i < n_; ++i) {
      if (used_[i] == 0) {
        Dfs1(i);
      }
    }
    std::reverse(order_.begin(), order_.end());
  }

  void Condensation() {
    for (auto u : order_) {
      if (comp_[u] == 0) {
        Dfs2(u);
        ++cnt_;
      }
    }
  }

  void GetRes() {
    std::cout << cnt_ - 1 << "\n";
    for (int i = 0; i < n_; ++i) {
      std::cout << comp_[i] << " ";
    }
    std::cout << "\n";
  }
};

signed main() {
  SpeedUp();
  Graph my_graph;
  my_graph.Init();
  my_graph.TopSort();
  my_graph.Condensation();
  my_graph.GetRes();
  return 0;
}
