#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int FindTheMinimumNumberOfPossiblePositionsISuchThatA_iNotEqB_iAfterKTransformations(const std::string& a, const std::string& b, int k) {
  std::vector<std::vector<std::vector<int>>> dp(2, std::vector<std::vector<int>>(k + 1, std::vector<int> (k + 1, 0)));

  int sz_a = a.size();
  int sz_b = b.size();

  int res = -1;
  for (int dl = 1; dl <= sz_b; ++dl) {
    for (int rem = 0; rem <= k && rem <= sz_a; ++rem) {
      for (int add = 0; add + rem <= k && add <= dl; ++add) {
        if (add > 0) {
          dp[dl % 2][rem][add] = std::max(dp[dl % 2][rem][add], dp[(dl - 1) % 2][rem][add - 1] + 1);
        }
        if (rem > 0) {
          dp[dl % 2][rem][add] = std::max(dp[dl % 2][rem][add], dp[dl % 2][rem - 1][add]);
        }
        if (dl + rem - add > 0 && dl + rem - add - 1 < sz_a) {
          dp[dl % 2][rem][add] = std::max(dp[dl % 2][rem][add],
                                      dp[(dl - 1) % 2][rem][add] + (a[dl + rem - add - 1] == b[dl - 1]));
        }
        if (sz_b + rem - add == sz_a) {
          res = std::max(res, dp[dl % 2][rem][add] + (k - rem - add));
        }
      }
    }
  }
  if (res != -1) {
    return std::max(0, sz_b - res);
  }
  return res;
}



int main() {
  std::string a, b;
  int k;
  std::cin >> a >> b >> k;

  int ans = FindTheMinimumNumberOfPossiblePositionsISuchThatA_iNotEqB_iAfterKTransformations(a, b, k);

  std::cout << ans << "\n";
  return 0;
}
