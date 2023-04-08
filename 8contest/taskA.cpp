#include <iostream>
#include <set>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

class Graph {
 private:
  const int kInf = 2009000999;

  int num_vert_;
  std::vector<std::vector<std::pair<int, int>>> graph_;

 public:
  Graph(int num_vert,
        const std::vector<std::vector<std::pair<int, int>>>& graph)
      : num_vert_(num_vert), graph_(graph) {}

  std::vector<int> Dijkstra(int start) const {
    std::vector<int> dist(num_vert_, kInf);
    dist[start] = 0;
    std::set<std::pair<int, int>> pool;
    pool.insert({dist[start], start});
    while (!pool.empty()) {
      int cur_v = (*pool.begin()).second;
      int cur_d = (*pool.begin()).first;
      pool.erase(pool.begin());
      if (cur_d > dist[cur_v]) {
        continue;
      }
      for (auto elem : graph_[cur_v]) {
        int to = elem.first;
        int weight = elem.second;
        if (dist[to] > dist[cur_v] + weight) {
          dist[to] = dist[cur_v] + weight;
          pool.insert({dist[to], to});
        }
      }
    }
    return dist;
  }
};

void Solve() {
  int num_vert;
  int num_edj;
  std::cin >> num_vert >> num_edj;
  std::vector<std::vector<std::pair<int, int>>> graph(num_vert);
  for (int j = 0; j < num_edj; ++j) {
    int v1;
    int v2;
    int weight;
    std::cin >> v1 >> v2 >> weight;
    graph[v1].push_back({v2, weight});
    graph[v2].push_back({v1, weight});
  }
  int start;
  std::cin >> start;
  Graph my_graph(num_vert, graph);
  std::vector<int> res = my_graph.Dijkstra(start);
  for (auto val : res) {
    std::cout << val << " ";
  }
  std::cout << "\n";
}

int main() {
  SpeedUp();
  int amount_of_tests;
  std::cin >> amount_of_tests;
  for (int i = 0; i < amount_of_tests; ++i) {
    Solve();
  }
}
