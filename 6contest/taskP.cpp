#include <iostream>
#include <string>
#include <vector>

const int kMod = 1'000'000'007;
const int kUnused = -1;

bool Check(int n, int mask, int pos, const std::vector<std::string>& map) {
  for (int i = 0; i < n; ++i) {
    if (map[i][pos] == '+' && ((mask >> i) & 1) == 0) {
      return false;
    }
    if (map[i][pos] == '-' && ((mask >> i) & 1) != 0) {
      return false;
    }
  }
  return true;
}

bool IsThereCorresponing(int n, int mask, int& opp) {
  for (int j = 1; j < n; ++j) {
    int cur = ((mask >> j) & 1) + ((mask >> (j - 1)) & 1);
    int sum = ((opp >> j) & 1) + ((opp >> (j - 1)) & 1);
    if (cur == 0) {
      if (sum == 0) {
        return false;
      }
      if (sum == 1) {
        opp += (1LL << j);
      }
    } else if (cur == 1) {
      if (sum == 0) {
        opp += (1LL << j);
      } else if (sum == 1) {
        continue;
      }
    } else if (cur == 2) {
      if (sum == 0) {
        continue;
      }
      return false;
    }
  }
  return true;
}

signed main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> map(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> map[i];
  }
  std::vector<std::vector<int>> dp(m, std::vector<int>(1LL << n, kUnused));
  //  dp[i][j] - количество различных вариантов распределения районов города на
  //  безоружные и излишне защищенные на префиксе карты района размера i,
  //  если в i-том столбце распределние районов соответствует битовой маске j
  for (int mask = 0; mask < (1LL << n); ++mask) {
    if (Check(n, mask, 0, map)) {
      dp[0][mask] = 1;
    }
  }
  for (int i = 1; i < m; ++i) {
    for (int mask = 0; mask < (1LL << n); ++mask) {
      if (Check(n, mask, i, map)) {
        int res = 0;

        int opp = 0;
        if (IsThereCorresponing(n, mask, opp) && dp[i - 1][opp] != kUnused) {
          res += dp[i - 1][opp];
          res %= kMod;
        }

        opp = 1;
        if (IsThereCorresponing(n, mask, opp) && dp[i - 1][opp] != kUnused) {
          res += dp[i - 1][opp];
          res %= kMod;
        }

        if (res != 0) {
          dp[i][mask] = res;
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < (1LL << n); ++i) {
    if (dp[m - 1][i] != kUnused) {
      ans += dp[m - 1][i];
      ans %= kMod;
    }
  }
  std::cout << ans << "\n";
}
