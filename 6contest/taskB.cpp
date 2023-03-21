#include <algorithm>
#include <iostream>
#include <vector>

const int kInf = 2147483647;

struct AnsForPrefix {
  int val = kInf;
  int pos = -1;
};

int BinarySearch(const std::vector<AnsForPrefix>& dp, int x) {
  int l = 0, r = dp.size();
  while (l + 1 < r) {
    int m = (l + r) / 2;
    if (dp[m].val <= x) {
      l = m;
    } else {
      r = m;
    }
  }
  return l + 1;
}

std::vector<int> Solve(int n, std::vector<int> s) {
  for (int i = 0; i < n; ++i) {
    s[i] *= -1;  // умножаю минус на -1, так как найдётся -a<-b<...<-x - что
                 // равносильно a>b>...>x - а это нам и нужно
  }
  std::vector<int> answer, parent(n, -1);
  std::vector<AnsForPrefix> dp(n + 1);  // d[i] (i = 0...n) — это число, на
                                        // которое оканчивается возрастающая
                                        // подпоследовательность длины i
                                        // (а если таких чисел несколько —
                                        // то наименьшее из них).
  dp[0].val = -kInf;
  int len = 0;

  for (int i = 0; i < n; ++i) {
    int pos = BinarySearch(dp, s[i]);
    if (dp[pos - 1].val <= s[i] && s[i] < dp[pos].val) {
      dp[pos].val = s[i];
      dp[pos].pos = i;
      parent[i] = dp[pos - 1].pos;
      len = std::max(len, pos);
    }
  }
  int pos = dp[len].pos;
  while (pos != -1) {
    answer.push_back(pos);
    pos = parent[pos];
  }
  return answer;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
  }
  std::vector<int> answer;
  answer = Solve(n, s);
  std::cout << answer.size() << "\n";
  std::reverse(answer.begin(), answer.end());
  for (auto x : answer) {
    std::cout << x + 1 << " ";
  }
  return 0;
}
