#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int dp[1000][100000] = {{0}};

int GetRes(int k, int res) {
  if (k > res) {
    return GetRes(res, res);
  }
  if (k == 0 || res == 0) {
    return 0;
  }
  if (k == 1) {
    return res;
  }
  if (dp[k][res] == 0) {
    dp[k][res] = GetRes(k, res - 1) + GetRes(k - 1, res - 1) + 1;
  }
  return dp[k][res];
}

signed main() {
  SpeedUp();
  int n, k;
  std::cin >> n >> k;

  if (n == 1) {
    std::cout << "0\n";
    return 0;
  }

  if (k == 0) {
    std::cout << "-1\n";
    return 0;
  }
  int res = 1;
  while (GetRes(k, res) < n - 1) {
    ++res;
  }
  std::cout << res << "\n";
}
