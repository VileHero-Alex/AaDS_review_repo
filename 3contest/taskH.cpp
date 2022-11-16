#include <algorithm>
#include <iostream>
#include <vector>

class SparseTable {
 private:
  const int kInf = static_cast<int>(1e9);
  std::vector<int> lg_, myCopy_;
  std::vector<std::vector<std::pair<int, int>>> table_;
  std::pair<int, int> GetValToMerge(std::pair<int, int> v1,
                                    std::pair<int, int> v2) {
    std::vector<int> temp = {v1.first, v1.second, v2.first, v2.second};
    std::sort(temp.begin(), temp.end(), [&](int p1, int p2) {
      if (p1 == kInf) {
        if (p2 == kInf) {
          return true;
        }
        return p1 < p2;
      }
      if (p2 == kInf) {
        return p1 < p2;
      }
      return myCopy_[p1] < myCopy_[p2];
    });
    temp.resize(std::unique(temp.begin(), temp.end()) - temp.begin());
    return {temp[0], temp[1]};
  }

  int GetAns(std::pair<int, int> v1, std::pair<int, int> v2) {
    std::vector<int> temp = {v1.first, v1.second, v2.first, v2.second};
    std::sort(temp.begin(), temp.end(), [&](int p1, int p2) {
      if (p1 == kInf) {
        if (p2 == kInf) {
          return true;
        }
        return p1 < p2;
      }
      if (p2 == kInf) {
        return p1 < p2;
      }
      return myCopy_[p1] < myCopy_[p2];
    });
    temp.resize(std::unique(temp.begin(), temp.end()) - temp.begin());
    return temp[1];
  }

 public:
  SparseTable(int n, std::vector<int>& arr) {
    lg_.assign(n + 1, 0);
    myCopy_.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      myCopy_[i] = arr[i];
    }
    for (int i = 2; i <= n; i++) {
      lg_[i] = lg_[i / 2] + 1;
    }
    table_.assign(lg_[n] + 1,
                  std::vector<std::pair<int, int>>(n, {kInf, kInf}));
    for (int i = 0; i < n; ++i) {
      table_[0][i] = {i, kInf};
    }
    for (int log_sz = 1; log_sz <= lg_[n]; ++log_sz) {
      for (int i = 0; i + (1LL << log_sz) <= n; ++i) {
        table_[log_sz][i] =
            GetValToMerge(table_[log_sz - 1][i],
                          table_[log_sz - 1][i + (1LL << (log_sz - 1))]);
      }
    }
  }

  int GetRes(int l, int r) {
    int seg_sz = lg_[r - l + 1];
    return GetAns(table_[seg_sz][l], table_[seg_sz][r - (1LL << seg_sz) + 1]);
  }
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
  SparseTable mns(n, a);
  for (int i = 0; i < q; ++i) {
    int l, r;
    std::cin >> l >> r;
    if (l > r) {
      std::swap(l, r);
    }
    --l, --r;
    std::cout << a[mns.GetRes(l, r)] << "\n";
  }
}

signed main() {
  SpeedUp();
  Solve();
  return 0;
}
