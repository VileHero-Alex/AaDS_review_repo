#include <iostream>
#include <vector>

int Solve(int n, int k) {
  if (k == 0) {
    if (n == 1) {
      return 0;
    }
    return -1;
  }
  std::vector<int> dp(k + 1, 0);
  // количество яиц, которые нужно бросить, чтобы
  // определить этаж, если номер этажа равен i
  int res = 0;
  while (dp[k] < n - 1) {
    for (int cur = k; cur > 0; --cur) {
      dp[cur] += dp[cur - 1] + 1;
    }
    ++res;
  }
  return res;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::cout << Solve(n, k);
}
