#include <iostream>
#include <vector>

class Knapsack {
 private:
  int n_, m_;
  std::vector<int> w_, c_, res_;
  std::vector<std::vector<int>> dp_, parent_;

 public:
  void Init() {
    std::cin >> n_ >> m_;
    dp_.assign(
        2,
        std::vector<int>(
            m_ + 1,
            -1));  // dp_[i][j] - максимальная стоимость предметов,
                   // которые можно набрать среди первых i с суммарным весом j
    parent_.assign(n_ + 1, std::vector<int>(m_ + 1, -1));
    w_.resize(n_ + 1);
    c_.resize(n_ + 1);
    for (int i = 1; i <= n_; ++i) {
      std::cin >> w_[i];
    }
    for (int i = 1; i <= n_; ++i) {
      std::cin >> c_[i];
    }
  }

  void Solve() {
    dp_[0][0] = 0;
    for (int i = 1; i <= n_; ++i) {
      dp_[i % 2] = dp_[(i - 1) % 2];
      for (int j = m_ - w_[i]; j >= 0; --j) {
        if (dp_[(i - 1) % 2][j] != -1 &&
            dp_[i % 2][j + w_[i]] < dp_[(i - 1) % 2][j] + c_[i]) {
          dp_[i % 2][j + w_[i]] =
              std::max(dp_[i % 2][j + w_[i]], dp_[(i - 1) % 2][j] + c_[i]);
          parent_[i][j + w_[i]] = i;
        }
      }
    }
    int mx = 0, val = 0;
    for (int i = 0; i <= m_; ++i) {
      if (mx < dp_[n_ % 2][i]) {
        mx = dp_[n_ % 2][i];
        val = i;
      }
    }
    while (val != 0) {
      if (parent_[n_][val] == -1) {
        --n_;
      } else {
        res_.push_back(parent_[n_][val]);
        val -= w_[n_];
        --n_;
      }
    }
  }

  void PrintRes() {
    for (auto x : res_) {
      std::cout << x << "\n";
    }
  }
};

int main() {
  Knapsack my_knapsack;
  my_knapsack.Init();
  my_knapsack.Solve();
  my_knapsack.PrintRes();
  return 0;
}
