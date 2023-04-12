#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int to, num;
};

class Graph {
 private:
    int n_, m_;
    std::vector<std::vector<Edge>> gr_;
    std::vector<int> used_, dp_, height_, res_;

 public:
    Graph(int n, int m, const std::vector<std::vector<Edge>>& gr): n_(n), m_(m), gr_(gr) {
      used_.resize(n_);
      dp_.resize(n_);
      height_.resize(n_);
    }

    void FindBridges() {
      for (int i = 0; i < n_; ++i) {
        if (used_[i] == 0) {
          Dfs(i);
        }
      }
    }
    
    void Dfs(int v, Edge p = {-1, -1}) {
      used_[v] = 1;
      dp_[v] = height_[v] = (p.num == -1 ? 0 : height_[p.to] + 1);
      for (auto ed : gr_[v]) {
        if (ed.num != p.num) {
          if (used_[ed.to] == 1) {
            dp_[v] = std::min(dp_[v], height_[ed.to]);
          } else {
            Dfs(ed.to, {v, ed.num});
            dp_[v] = std::min(dp_[v], dp_[ed.to]);
            if (height_[v] < dp_[ed.to]) {
              res_.push_back(ed.num);
            }
          }
        }
      }
    }

    void PrintAllBridges() {
      std::cout << res_.size() << "\n";
      sort(res_.begin(), res_.end());
      for (auto x : res_) {
        std::cout << x << " ";
      }
    }
};


signed main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> gr(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    gr[u].push_back({v, i + 1});
    gr[v].push_back({u, i + 1});
  }
  Graph my_graph(n, m, gr);
  my_graph.FindBridges();
  my_graph.PrintAllBridges();
  return 0;
}
