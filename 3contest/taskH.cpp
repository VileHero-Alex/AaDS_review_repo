#include <algorithm>
#include <iostream>
#include <vector>

struct MyElement {
  int first_min, second_min;
};

class SparseTable {
 private:
  static const int kInf = static_cast<int>(1e9);
  std::vector<int> myCopy_, lg_;
  std::vector<std::vector<MyElement>> table_;

  MyElement GetValToMerge(MyElement v1, MyElement v2);

  int GetAns(MyElement v1, MyElement v2);

 public:
  SparseTable(std::vector<int>& arr);

  int GetRes(int l, int r);
};

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

void Solve() {
  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  SparseTable minimums(a);
  for (int i = 0; i < q; ++i) {
    int l, r;
    std::cin >> l >> r;
    if (l > r) {
      std::swap(l, r);
    }
    --l, --r;
    std::cout << a[minimums.GetRes(l, r)] << "\n";
  }
}

signed main() {
  SpeedUp();
  Solve();
  return 0;
}

int SparseTable::GetAns(MyElement v1, MyElement v2) {
  return GetValToMerge(v1, v2).second_min;
}

MyElement SparseTable::GetValToMerge(MyElement v1, MyElement v2) {
  std::vector<int> temp = {v1.first_min, v1.second_min, v2.first_min,
                           v2.second_min};
  std::sort(temp.begin(), temp.end(), [this](int p1, int p2) {
    if (p1 == kInf || p2 == kInf) {
      return p1 < p2;
    }
    return myCopy_[p1] < myCopy_[p2];
  });
  temp.resize(std::unique(temp.begin(), temp.end()) - temp.begin());
  return {temp[0], temp[1]};
}

SparseTable::SparseTable(std::vector<int>& arr)
    : myCopy_(arr), lg_(arr.size() + 1) {
  int n = static_cast<int>(arr.size());
  for (int i = 2; i <= n; i++) {
    lg_[i] = lg_[i / 2] + 1;
  }
  table_.assign(lg_[n] + 1, std::vector<MyElement>(n, {kInf, kInf}));
  for (int i = 0; i < n; ++i) {
    table_[0][i] = {i, static_cast<int>(kInf)};
  }
  for (int log_sz = 1; log_sz <= lg_[n]; ++log_sz) {
    for (int i = 0; i + (1LL << log_sz) <= n; ++i) {
      table_[log_sz][i] = GetValToMerge(
          table_[log_sz - 1][i], table_[log_sz - 1][i + (1LL << (log_sz - 1))]);
    }
  }
}

int SparseTable::GetRes(int l, int r) {
  int seg_sz = lg_[r - l + 1];
  return GetAns(table_[seg_sz][l], table_[seg_sz][r - (1LL << seg_sz) + 1]);
}
