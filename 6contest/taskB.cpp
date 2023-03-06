#include <algorithm>
#include <iostream>
#include <vector>

const int kInf = 2147483647;

int BinarySearch(std::vector<int>& dp, int x) {
  int l = 0, r = dp.size();
  while (l + 1 < r) {
    int m = (l + r) / 2;
    if (dp[m] <= x) {
      l = m;
    } else {
      r = m;
    }
  }
  return l + 1;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
    s[i] *= -1;
  }
  std::vector<int> dp(n + 1, kInf), dp_pos(n + 1, -1), parent(n, -1);
  dp[0] = -kInf;
  int len = 0;

  for (int i = 0; i < n; ++i) {
    int pos = BinarySearch(dp, s[i]);
    if (dp[pos - 1] <= s[i] && s[i] < dp[pos]) {
      dp[pos] = s[i];
      dp_pos[pos] = i;
      parent[i] = dp_pos[pos - 1];
      len = std::max(len, pos);
    }
  }
  std::vector<int> answer;
  int pos = dp_pos[len];
  while (pos != -1) {
    answer.push_back(pos);
    pos = parent[pos];
  }
  std::cout << len << "\n";
  std::reverse(answer.begin(), answer.end());
  for (auto x : answer) {
    std::cout << x + 1 << " ";
  }

  return 0;
}
