#include <algorithm>
#include <iostream>
#include <string>

int q;
std::string t;
int queue[(int)2e5 + 100];
int mins[(int)2e5 + 100];
int q_l = 0, q_r = 0, mn_l = 0, mn_r = 0;

int Size() { return (q_r - q_l); }

void Enqueue() {
  int x;
  std::cin >> x;
  queue[q_r] = x;
  q_r++;
  while (mn_l < mn_r && mins[mn_r - 1] > x) {
    mn_r--;
  }
  mins[mn_r] = x;
  mn_r++;
  std::cout << "ok\n";
}

void Dequeue() {
  if (Size() == 0) {
    std::cout << "error\n";
    return;
  }
  if (queue[q_l] == mins[mn_l]) {
    mn_l++;
  }
  std::cout << queue[q_l] << "\n";
  q_l++;
}

void Front() {
  if (Size() == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << queue[q_l] << "\n";
}

void Clear() {
  q_l = q_r = 0;
  mn_l = mn_r = 0;
  std::cout << "ok\n";
}

void FindMin() {
  if (Size() == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << mins[mn_l] << "\n";
}

int main() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin >> q;
  for (int que = 0; que < q; ++que) {
    std::cin >> t;
    if (t == "enqueue") {
      Enqueue();
    }
    if (t == "dequeue") {
      Dequeue();
    }
    if (t == "front") {
      Front();
    }
    if (t == "size") {
      std::cout << Size() << "\n";
    }
    if (t == "clear") {
      Clear();
    }
    if (t == "min") {
      FindMin();
    }
  }
}
