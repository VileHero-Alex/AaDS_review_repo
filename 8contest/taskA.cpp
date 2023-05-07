#include <iostream>
#include <set>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

struct Node {
  int to;
  int weight;
};

struct NodeCmp {
  bool operator()(const Node& first, const Node& second) const {
    if (first.weight != second.weight) {
      return first.weight < second.weight;
    }
    return first.to < second.to;
  }
};

class Graph {
 private:
  static constexpr const int kInf = 2009000999;

  int num_vert_;
  std::vector<std::vector<Node>> graph_;

 public:
  Graph(int num_vert, const std::vector<std::vector<Node>>& graph)
      : num_vert_(num_vert), graph_(graph) {}

  std::vector<int> Dijkstra(int start) const {
    std::vector<int> dist(num_vert_, kInf);
    dist[start] = 0;
    std::set<Node, NodeCmp> pool;
    pool.insert({start, dist[start]});
    while (!pool.empty()) {
      int cur_v = (*pool.begin()).to;
      int cur_d = (*pool.begin()).weight;
      pool.erase(pool.begin());
      if (cur_d > dist[cur_v]) {
        continue;
      }
      for (auto [to, weight] : graph_[cur_v]) {
        if (dist[to] > dist[cur_v] + weight) {
          dist[to] = dist[cur_v] + weight;
          pool.insert({to, dist[to]});
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
  std::vector<std::vector<Node>> graph(num_vert);
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
