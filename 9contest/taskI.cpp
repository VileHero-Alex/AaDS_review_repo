#include <algorithm>
#include <iostream>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

class Graph {
 private:

  int m, n;
  std::vector<std::vector<int>> left;
  std::vector<int> match;
  std::vector<std::vector<int>> special_graph;

  std::vector<int> res_left, res_right;
  std::vector<bool> used;

  void Dfs(int u) {
    used[u] = 1;
    for (auto v : special_graph[u]) {
      if (!used[v]) {
        Dfs(v);
      }
    }
  }

 public:

  void ReadData() {
    std::cin >> m >> n;
    left.resize(m);
    match.resize(m);
    special_graph.resize(n + m);
    for (int i = 0; i < m; ++i) {
      int k;
      std::cin >> k;
      for (int j = 0; j < k; ++j) {
        int u;
        std::cin >> u;
        --u;
        left[i].push_back(u);
      }
    }
    for (int i = 0; i < m; ++i) {
      std::cin >> match[i];
      --match[i];
    }
    for (int i = 0; i < m; ++i) {
      for (auto v : left[i]) {
        if (match[i] == v) {
          special_graph[m + v].push_back(i);
        } else {
          special_graph[i].push_back(m + v);
        }
      }
    }
  }

  void FindMinimumControlSet() {
    used.resize(n + m);
    for (int i = 0; i < m; ++i) {
      if (match[i] == -1) {
        Dfs(i);
      }
    }
    for (int i = 0; i < n + m; ++i) {
      if (i < m && used[i] == 0) {
        res_left.push_back(i);
      } else if (i >= m && used[i] == 1) {
        res_right.push_back(i - m);
      }
    }
  }

  void PrintRes() {
    std::cout << res_left.size() + res_right.size() << "\n";
    std::cout << res_left.size() << " ";
    for (auto v : res_left) {
      std::cout << v + 1 << " ";
    }
    std::cout << "\n" << res_right.size() << " ";
    for (auto v : res_right) {
      std::cout << v + 1 << " ";
    }
  }
};

void Solve() {
  Graph my_graph;
  my_graph.ReadData();
  my_graph.FindMinimumControlSet();
  my_graph.PrintRes();
}

signed main() {
  SpeedUp();
  Solve();
}
