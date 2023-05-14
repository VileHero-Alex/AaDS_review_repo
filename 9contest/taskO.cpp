#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

class Graph {
 private:
  static constexpr const int kIntInf = INT32_MAX;
  static constexpr const double kDoubleInf = 1e20;
  static constexpr const double kEps = 0.00001;

  int n_, m_;

  std::vector<std::vector<int>> graph_;
  std::vector<int> degs_, dist_, ptrs_;
  std::vector<bool> used_;
  std::vector<std::vector<double>> capacity_;

   double Dfs(int v, int finish, double mnEps = kDoubleInf) {
    if (v == finish || mnEps < kEps) {
      return mnEps;
    }
    for (int u = ptrs_[v]; u < static_cast<int>(graph_.size()); ++u) {
      if (dist_[u] != dist_[v] + 1) {
        ++ptrs_[v];
        continue;
      }
      double delta = Dfs(u, finish, std::min(mnEps, capacity_[v][u]));
      if (std::abs(delta) > kEps) {
        capacity_[u][v] += delta;
        capacity_[v][u] -= delta;
        return delta;
      }
      ++ptrs_[v];
    }
    return 0;
  }
  
  bool Bfs(int start, int finish) {

    std::queue<int> pool;

    dist_.assign(graph_.size(), kIntInf);
    dist_[start] = 0;
    
    pool.push(start);

    while (!pool.empty()) {
      int v = pool.front();
      pool.pop();
      for (auto u : graph_[v]) {
        if (capacity_[v][u] > kEps && dist_[u] == kIntInf) {
          dist_[u] = dist_[v] + 1;
          pool.push(u);
        }
      }
    }
    return dist_[finish] != kIntInf;
  }

  double FindMaxFlow(int start, int finish) {
    size_t conunt_of_vertex = capacity_.size();
    dist_.assign(conunt_of_vertex, kIntInf);

    double maxFlow = 0;

    while (Bfs(start, finish)) {
      ptrs_.assign(conunt_of_vertex, 0);
      double cur_flow = 0;
      do {
        cur_flow = Dfs(start, finish);
        maxFlow += cur_flow;
      } while (cur_flow > kEps);
    }
    return maxFlow;
  }

  double GetFlow(double density) {

    capacity_.assign(n_ + 2, std::vector<double>(n_ + 2, 0));
    for (int i = 0; i < n_; ++i) {
      for (int j : graph_[i]) {
        capacity_[i][j] = 1;
      }
    }
    for (int i = 0; i < n_; ++i) {
      capacity_[n_][i] = 2 * density;
      capacity_[i][n_ + 1] = degs_[i];
    }

    return FindMaxFlow(n_, n_ + 1);
  }

  void FirstSearch(int v) {
    used_[v] = true;
    for (auto u : graph_[v]) {
      if (!used_[u] && capacity_[v][u] > kEps) {
        FirstSearch(u);
      }
    }
  }

 public:

  void RestoreExactAns(double density) {

    capacity_.assign(n_ + 2, std::vector<double>(n_ + 2, 0));

    for (int i = 0; i < n_; ++i) {
      for (int j : graph_[i]) {
        capacity_[i][j] = 1;
      }
    }
    for (int i = 0; i < n_; ++i) {
      capacity_[n_][i] = 2 * density;
      capacity_[i][n_ + 1] = degs_[i];
    }

    FindMaxFlow(n_, n_ + 1);

    used_.assign(n_ + 2, false);

    FirstSearch(n_);
    int cnt = 0;
    for (int i = 0; i < n_ + 2; ++i) {
      if (!used_[i]) {
        ++cnt;
      }
    }
    std::cout << cnt - 1 << "\n";
    for (int i = 0; i < n_ + 2; ++i) {
      if (!used_[i] && i != n_ + 1) {
        std::cout << i + 1 << "\n";
      }
    }
  }

  void ReadData() {
    std::cin >> n_ >> m_;

    degs_.assign(n_, 0);
    graph_.assign(n_ + 2, std::vector<int>());

    for (int i = 0; i < n_; ++i) {
      graph_[n_].push_back(i);
      graph_[i].push_back(n_ + 1);
    }
    for (int i = 0; i < m_; ++i) {
      int v1, v2;
      std::cin >> v1 >> v2;
      --v1;
      --v2;
      ++degs_[v1];
      ++degs_[v2];
      graph_[v1].push_back(v2);
      graph_[v2].push_back(v1);
    }
  }

  void BinarySearchForAns() {
    double l = 0;
    double r = m_;

    if (m_ == 0) {
      std::cout << "1\n1\n";
      return;
    }

    double density;

    for (int i = 0; i < 40; ++i) {
      density = (l + r) / 2;
      double flow = GetFlow(density);
      if (kEps < 2.0 * m_ - flow) {
        l = density;
      } else {
        r = density;
      }
    }
    RestoreExactAns(r - 1.0 / (n_ * n_));
  }

};

void Solve() {
  Graph my_graph;

  my_graph.ReadData();
  my_graph.BinarySearchForAns();
  
}

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  SpeedUp();
  Solve();
  return 0;
}
