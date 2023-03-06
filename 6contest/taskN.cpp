#include <algorithm>
#include <iostream>
#include <string>
#include <vector>



int main() {
  std::string a, b;
  int k;
  std::cin >> a >> b >> k;

  std::vector<std::vector<std::vector<int>>> dp(b.size() + k + 1, std::vector<std::vector<int>>(k + 1, std::vector<int> (k + 1, 0)));
  bool fl = false;
  int res = 0;
  for (int dl = 1; dl <= (int)b.size(); ++dl) {
    for (int rem = 0; rem <= k && rem <= (int)a.size(); ++rem) {
      for (int add = 0; add + rem <= k && add <= dl; ++add) {
        if (add > 0) {
          dp[dl][rem][add] = std::max(dp[dl][rem][add], dp[dl - 1][rem][add - 1] + 1);
        }
        if (rem > 0) {
          dp[dl][rem][add] = std::max(dp[dl][rem][add], dp[dl][rem - 1][add]);
        }
        if (dl + rem - add > 0 && dl + rem - add - 1 < (int)a.size()) {
          dp[dl][rem][add] = std::max(dp[dl][rem][add],
                                      dp[dl - 1][rem][add] + (a[dl + rem - add - 1] == b[dl - 1]));
        }
        if ((int)b.size() + rem - add == (int)a.size()) {
          fl = true;
          res = std::max(res, dp[dl][rem][add] + (k - rem - add));
        }
      }
    }
  }

  if (fl) {
    std::cout << std::max(0, (int)b.size() - res);
  } else {
    std::cout << "-1\n";
  }
  return 0;
}
