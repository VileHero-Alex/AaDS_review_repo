#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int n;
int data[(int)1e5 + 100];

int Rnd(int lf, int rt) {
  std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
  return lf + rnd() % (rt - lf);
}

void QuickSort(int lf, int rt) {
  if (lf + 1 >= rt) {
    return;
  }
  int md = data[Rnd(lf, rt)], pos = lf;
  for (int i = lf; i < rt; ++i) {
    if (data[i] < md) {
      std::swap(data[i], data[pos++]);
    }
  }
  QuickSort(lf, pos);
  for (int i = pos; i < rt; i++) {
    if (data[i] == md) {
      std::swap(data[i], data[pos++]);
    }
  }
  QuickSort(pos, rt);
}

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

void Init() {
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> data[i];
  }
}

void Solve() {
  QuickSort(0, n);
  for (int i = 0; i < n; ++i) {
    std::cout << data[i] << " ";
  }
}

int main() {
  SpeedUp();
  Init();
  Solve();
  return 0;
}
