#include <iostream>
#include <vector>

void StableSort(int n, std::vector<long long>& col, std::vector<int>& per) {
  std::vector<int> cnt(256, 0), res(n);
  for (int i = 0; i < n; ++i) {
    ++cnt[col[per[i]]];
  }
  for (int i = 0; i + 1 < 256; ++i) {
    cnt[i + 1] += cnt[i];
  }
  for (int i = n - 1; i >= 0; --i) {
    --cnt[col[per[i]]];
    res[cnt[col[per[i]]]] = per[i];
  }
  per = res;
}

void Solve() {
  int n;
  std::cin >> n;
  std::vector<int> permutation(n);
  for (int i = 0; i < n; ++i) {
    permutation[i] = i;
  }
  std::vector<long long> a(n), quotient(n), column(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    quotient[i] = a[i];
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < n; ++j) {
      column[j] = quotient[j] % 256;
      quotient[j] /= 256;
    }
    StableSort(n, column, permutation);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << a[permutation[i]] << "\n";
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
