#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Graph {
 private:
    struct Edge {
      int to, num;
    };

    int n, m;
    std::vector<std::vector<Edge>> gr;
    std::vector<int> used, dp, hight, res;

 public:
    void Init() {
      std::cin >> n >> m;
      gr.resize(n);
      used.resize(n);
      dp.resize(n);
      hight.resize(n);
      for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        gr[u].push_back({v, i + 1});
        gr[v].push_back({u, i + 1});
      }
    }

    void FindBridges() {
      for (int i = 0; i < n; ++i) {
        if (used[i] == 0) {
          Dfs(i);
        }
      }
    }
    
    void Dfs(int v, Edge p = {-1, -1}) {
      used[v] = 1;
      dp[v] = hight[v] = (p.num == -1 ? 0 : hight[p.to] + 1);
      for (auto ed : gr[v]) {
        if (ed.num != p.num) {
          if (used[ed.to] == 1) {
            dp[v] = std::min(dp[v], hight[ed.to]);
          } else {
            Dfs(ed.to, {v, ed.num});
            dp[v] = std::min(dp[v], dp[ed.to]);
            if (hight[v] < dp[ed.to]) {
              res.push_back(ed.num);
            }
          }
        }
      }
    }

    void GetRes() {
      std::cout << res.size() << "\n";
      sort(res.begin(), res.end());
      for (auto x : res) {
        std::cout << x << " ";
      }
    }
};


signed main() {
  Graph MyGraph;
  MyGraph.Init();
  MyGraph.FindBridges();
  MyGraph.GetRes();
  return 0;
}
