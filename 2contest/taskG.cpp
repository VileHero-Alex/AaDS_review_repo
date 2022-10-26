#include <iostream>
#include <vector>

void StableSort(int n, std::vector<long long>& col,
                std::vector<long long>& per) {
  const long long kSz = 256;
  std::vector<long long> cnt(kSz, 0), res(n);
  for (int i = 0; i < n; ++i) {
    ++cnt[col[per[i]]];
  }
  for (int i = 0; i + 1 < kSz; ++i) {
    cnt[i + 1] += cnt[i];
  }
  for (int i = n - 1; i >= 0; --i) {
    --cnt[col[per[i]]];
    res[cnt[col[per[i]]]] = per[i];
  }
  per = res;
}

std::vector<long long> GetSort(std::vector<long long> a) {
  const long long kDiv = 8;
  int n = a.size();
  std::vector<long long> permutation(n), quotient(n), column(n);
  for (int i = 0; i < n; ++i) {
    permutation[i] = i;
  }
  for (int i = 0; i < n; ++i) {
    quotient[i] = a[i];
  }
  for (int i = 0; i < kDiv; ++i) {
    for (int j = 0; j < n; ++j) {
      column[j] = quotient[j] & ((1 << kDiv) - 1);
      quotient[j] >>= kDiv;
    }
    StableSort(n, column, permutation);
  }
  std::vector<long long> res(n);
  for (int i = 0; i < n; ++i) {
    res[i] = a[permutation[i]];
  }
  return res;
}

void Solve() {
  int n;
  std::cin >> n;
  std::vector<long long> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<long long> ans = GetSort(a);
  for (int i = 0; i < n; ++i) {
    std::cout << ans[i] << "\n";
  }
}

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  SpeedUp();
  Solve();
  return 0;
}
