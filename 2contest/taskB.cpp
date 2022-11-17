#include <chrono>
#include <iostream>
#include <random>
#include <vector>

namespace MyConst {
const int kMod = static_cast<int>(1e7) + 4321;
}

int Rnd(int lf, int rt) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(lf, rt);
  return distrib(gen);
}

void Partition(int lf, int rt, int& md, int& pos, int* data) {
  md = data[Rnd(lf, rt)], pos = lf;
  for (int i = lf; i < rt; ++i) {
    if (data[i] < md) {
      std::swap(data[i], data[pos++]);
    }
  }
}

void PostPartition(int& pos, int rt, int md, int* data) {
  for (int i = pos; i < rt; ++i) {
    if (data[i] == md) {
      std::swap(data[i], data[pos++]);
    }
  }
}

int KthSearch(int lf, int rt, int k, int* data) {
  if (lf + 1 >= rt) {
    return data[lf];
  }
  int md, pos;
  Partition(lf, rt, md, pos, data);
  if (k <= pos - lf) {
    return KthSearch(lf, pos, k, data);
  }
  PostPartition(pos, rt, md, data);
  if (k <= pos - lf) {
    return data[pos - 1];
  }
  return KthSearch(pos, rt, k - (pos - lf), data);
}

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

void Solve() {
  int n, kth;
  std::cin >> n >> kth;
  int* data = new int[n];
  std::cin >> data[0] >> data[1];
  for (int i = 2; i < n; ++i) {
    data[i] = (data[i - 1] * 123 + data[i - 2] * 45) % MyConst::kMod;
  }
  std::cout << KthSearch(0, n, kth, data);
  delete[] data;
}

int main() {
  SpeedUp();
  Solve();
  return 0;
}
