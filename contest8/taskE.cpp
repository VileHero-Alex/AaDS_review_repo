#include <algorithm>
#include <iostream>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

struct Edge {
  int v1, v2, weight;
};

class Graph {
 private:
  const int kInf = 1'000'000'000;
  const int kNoVal = -1;
  int num_vert_;
  int num_edj_;
  std::vector<Edge> graph_;
  std::vector<int> path_;

 public:
  Graph(int num_vert, int num_edj, const std::vector<Edge>& graph)
      : num_vert_(num_vert), num_edj_(num_edj), graph_(graph) {}

  bool CheckForNegativeCycle(int start) {
    std::vector<int> dist(num_vert_, kInf);
    dist[start] = 0;
    std::vector<int> parent(num_vert_, kNoVal);
    int check = kNoVal;
    for (int i = 0; i < num_vert_; ++i) {
      check = kNoVal;
      for (int j = 0; j < num_edj_; ++j) {
        if (dist[graph_[j].v2] > dist[graph_[j].v1] + graph_[j].weight) {
          dist[graph_[j].v2] = std::min(dist[graph_[j].v2],
                                        dist[graph_[j].v1] + graph_[j].weight);
          parent[graph_[j].v2] = graph_[j].v1;
          check = graph_[j].v2;
        }
      }
    }
    if (check == kNoVal) {
      return false;
    }
    int begin = check;
    for (int i = 0; i < num_vert_; ++i) {
      begin = parent[begin];
    }
    for (int cur = begin;; cur = parent[cur]) {
      path_.push_back(cur);
      if (cur == begin && path_.size() > 1) {
        break;
      }
    }
    return true;
  }

  void PrintNegativeCycle() {
    std::cout << path_.size() << "\n";
    for (auto vert : path_) {
      std::cout << vert + 1 << " ";
    }
    std::cout << "\n";
  }
};

void Solve() {
  const int kNoEdj = 100000;
  int num_vert;
  std::cin >> num_vert;
  std::vector<Edge> graph;
  for (int i = 0; i < num_vert; ++i) {
    for (int j = 0; j < num_vert; ++j) {
      int weight;
      std::cin >> weight;
      if (weight != kNoEdj) {
        graph.push_back({j, i, weight});
      }
    }
  }
  Graph my_graph(num_vert, graph.size(), graph);
  bool is_cycle = my_graph.CheckForNegativeCycle(0);
  if (is_cycle) {
    std::cout << "YES\n";
    my_graph.PrintNegativeCycle();
  } else {
    std::cout << "NO\n";
  }
}

int main() {
  SpeedUp();
  Solve();
}
