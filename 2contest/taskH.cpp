#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int Rnd(int lf, int rt) {
  std::mt19937 rnd(13);
  return lf + rnd() % (rt - lf);
}

void QuickSort(int lf, int rt, std::vector<int>& data) {
  if (lf + 1 >= rt) {
    return;
  }
  int md = data[Rnd(lf, rt)], pos = lf;
  for (int i = lf; i < rt; ++i) {
    if (data[i] < md) {
      std::swap(data[i], data[pos++]);
    }
  }
  QuickSort(lf, pos, data);
  for (int i = pos; i < rt; ++i) {
    if (data[i] == md) {
      std::swap(data[i], data[pos++]);
    }
  }
  QuickSort(pos, rt, data);
}

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

void Solve() {
  int n;
  std::cin >> n;
  std::vector<int> data(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> data[i];
  }
  QuickSort(0, n, data);
  for (int i = 0; i < n; ++i) {
    std::cout << data[i] << " ";
  }
}

int main() {
  SpeedUp();
  Solve();
  return 0;
}
