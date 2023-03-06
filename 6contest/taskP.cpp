#include <iostream>
#include <string>
#include <vector>

const int kMod = 1'000'000'007;

bool Check(int n, int mask, int pos, std::vector<std::string>& s) {
  for (int i = 0; i < n; ++i) {
    if (s[i][pos] == '+' && ((mask >> i) & 1) == 0) {
      return false;
    }
    if (s[i][pos] == '-' && ((mask >> i) & 1) != 0) {
      return false;
    }
  }
  return true;
}

void MakeCorresponing(int n, int mask, int& opp, bool& fl) {
  for (int j = 1; j < n; ++j) {
    int cur = ((mask >> j) & 1) + ((mask >> (j - 1)) & 1);
    int sum = ((opp >> j) & 1) + ((opp >> (j - 1)) & 1);
    if (cur == 0) {
      if (sum == 0) {
        fl = false;
        break;
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
      fl = false;
      break;
    }
  }
}

signed main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
  }
  std::vector<std::vector<int>> dp(m, std::vector<int>(1LL << n, -1));
  for (int mask = 0; mask < (1LL << n); ++mask) {
    if (Check(n, mask, 0, s)) {
      dp[0][mask] = 1;
    }
  }
  for (int i = 1; i < m; ++i) {
    for (int mask = 0; mask < (1LL << n); ++mask) {
      if (Check(n, mask, i, s)) {
        int res = 0;

        int opp = 0;
        bool fl = true;
        MakeCorresponing(n, mask, opp, fl);

        if (fl && dp[i - 1][opp] != -1) {
          res += dp[i - 1][opp];
          res %= kMod;
        }

        opp = 1;
        fl = true;
        MakeCorresponing(n, mask, opp, fl);

        if (fl && dp[i - 1][opp] != -1) {
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
    if (dp[m - 1][i] != -1) {
      ans += dp[m - 1][i];
      ans %= kMod;
    }
  }
  std::cout << ans << "\n";
}
