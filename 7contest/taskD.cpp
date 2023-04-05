#include <algorithm>
#include <iostream>
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

  void DfsForFindingTopSortOfGraph(int v) {
    used_[v] = 1;
    for (auto u : graph_[v]) {
      if (used_[u] == 0) {
        DfsForFindingTopSortOfGraph(u);
      }
    }
    order_.push_back(v);
  }

  void DfsForDeterminingNoOfComponent(int v) {
    comp_[v] = cnt_;
    for (auto u : transp_[v]) {
      if (comp_[u] == 0) {
        DfsForDeterminingNoOfComponent(u);
      }
    }
  }

 public:
  Graph(int n, int m, const std::vector<std::vector<int>>& graph)
      : n_(n), m_(m), graph_(graph) {
    transp_.resize(n_);
    used_.resize(n_);
    comp_.resize(n_);
    for (int i = 0; i < n_; ++i) {
      for (auto u : graph_[i]) {
        transp_[u].push_back(i);
      }
    }
  }

  void TopSort() {
    for (int i = 0; i < n_; ++i) {
      if (used_[i] == 0) {
        DfsForFindingTopSortOfGraph(i);
      }
    }
    std::reverse(order_.begin(), order_.end());
  }

  void Condensation() {
    for (auto u : order_) {
      if (comp_[u] == 0) {
        DfsForDeterminingNoOfComponent(u);
        ++cnt_;
      }
    }
  }

  void PrintStrongCohesionComponents() {
    std::cout << cnt_ - 1 << "\n";
    for (int i = 0; i < n_; ++i) {
      std::cout << comp_[i] << " ";
    }
    std::cout << "\n";
  }
};

signed main() {
  SpeedUp();
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    graph[u].push_back(v);
  }
  Graph my_graph(n, m, graph);
  my_graph.TopSort();
  my_graph.Condensation();
  my_graph.PrintStrongCohesionComponents();
  return 0;
}
