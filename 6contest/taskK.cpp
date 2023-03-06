#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> w(n + 1), c(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> w[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> c[i];
  }
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, -1));
  std::vector<std::vector<int>> parent(n + 1, std::vector<int>(m + 1, -1));
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[i - 1];
    for (int j = m - w[i]; j >= 0; --j) {
      if (dp[i - 1][j] != -1 && dp[i][j + w[i]] < dp[i - 1][j] + c[i]) {
        dp[i][j + w[i]] = std::max(dp[i][j + w[i]], dp[i - 1][j] + c[i]);
        parent[i][j + w[i]] = i;
      }
    }
  }
  int mx = 0, val = 0;
  for (int i = 0; i <= m; ++i) {
    if (mx < dp[n][i]) {
      mx = dp[n][i];
      val = i;
    }
  }
  while (val != 0) {
    if (parent[n][val] == -1) {
      --n;
    } else {
      std::cout << parent[n][val] << "\n";
      val -= w[n];
      --n;
    }
  }
  return 0;
}
