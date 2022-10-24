#include <chrono>
#include <iostream>
#include <random>
#include <vector>

const int kMod = (int)1e7 + 4321;

int n, kth;
int res;
int data[(int)1e7 + 100];

int Rnd(int lf, int rt) {
  std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
  return lf + rnd() % (rt - lf);
}

void QuickSort(int lf, int rt, int k) {
  if (lf + 1 >= rt) {
    res = data[lf];
    return;
  }
  int md = data[Rnd(lf, rt)], pos = lf;
  for (int i = lf; i < rt; ++i) {
    if (data[i] < md) {
      std::swap(data[i], data[pos++]);
    }
  }
  if (k <= pos - lf) {
    QuickSort(lf, pos, k);
    return;
  }
  for (int i = pos; i < rt; i++) {
    if (data[i] == md) {
      std::swap(data[i], data[pos++]);
    }
  }
  if (k <= pos - lf) {
    res = data[pos - 1];
    return;
  }
  QuickSort(pos, rt, k - (pos - lf));
}

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

void Init() {
  std::cin >> n >> kth >> data[0] >> data[1];
  for (int i = 2; i < n; ++i) {
    data[i] = (data[i - 1] * 123 + data[i - 2] * 45) % kMod;
  }
}

void Solve() {
  QuickSort(0, n, kth);
  std::cout << res << "\n";
}

int main() {
  SpeedUp();
  Init();
  Solve();
  return 0;
}
