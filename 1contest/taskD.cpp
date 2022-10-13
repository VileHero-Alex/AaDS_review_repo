#include <algorithm>
#include <iostream>
#include <string>

struct SuperQueue {
  int* queue;
  int* mins;
  int q_l, q_r, mn_l, mn_r;

  SuperQueue() {
    q_l = 0;
    q_r = 0;
    mn_l = 0;
    mn_r = 0;
    queue = new int[(int)(2e5) + 100];
    mins = new int[(int)(2e5) + 100];
  }

  ~SuperQueue() {
    delete[] queue;
    delete[] mins;
  }

  int Size() const { return (q_r - q_l); }

  void Enqueue() {
    int x;
    std::cin >> x;
    queue[q_r] = x;
    ++q_r;
    while (mn_l < mn_r && mins[mn_r - 1] > x) {
      --mn_r;
    }
    mins[mn_r] = x;
    ++mn_r;
    std::cout << "ok\n";
  }

  void Dequeue() {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    if (queue[q_l] == mins[mn_l]) {
      ++mn_l;
    }
    std::cout << queue[q_l] << "\n";
    ++q_l;
  }

  void Front() const {
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

  void FindMin() const {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << mins[mn_l] << "\n";
  }
};

int main() {
  std::cin.tie(0);
  std::cout.tie(0);
  SuperQueue curr_queue;
  int q;
  std::cin >> q;
  std::string t;
  for (int que = 0; que < q; ++que) {
    std::cin >> t;
    if (t == "enqueue") {
      curr_queue.Enqueue();
    }
    if (t == "dequeue") {
      curr_queue.Dequeue();
    }
    if (t == "front") {
      curr_queue.Front();
    }
    if (t == "size") {
      std::cout << curr_queue.Size() << "\n";
    }
    if (t == "clear") {
      curr_queue.Clear();
    }
    if (t == "min") {
      curr_queue.FindMin();
    }
  }
}
