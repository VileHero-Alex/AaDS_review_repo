#include <algorithm>
#include <iostream>
#include <string>

class SuperQueue {
 private:
  const int kKSz = (int)(2e5) + 100;
  int* queue_;
  int* mins_;
  int q_l_, q_r_, mn_l_, mn_r_;

 public:
  SuperQueue() {
    q_l_ = 0;
    q_r_ = 0;
    mn_l_ = 0;
    mn_r_ = 0;
    queue_ = new int[kKSz];
    mins_ = new int[kKSz];
  }

  ~SuperQueue() {
    delete[] queue_;
    delete[] mins_;
  }

  int Size() const { return (q_r_ - q_l_); }

  void Enqueue() {
    int x;
    std::cin >> x;
    queue_[q_r_] = x;
    ++q_r_;
    while (mn_l_ < mn_r_ && mins_[mn_r_ - 1] > x) {
      --mn_r_;
    }
    mins_[mn_r_] = x;
    ++mn_r_;
    std::cout << "ok\n";
  }

  void Dequeue() {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    if (queue_[q_l_] == mins_[mn_l_]) {
      ++mn_l_;
    }
    std::cout << queue_[q_l_] << "\n";
    ++q_l_;
  }

  void Front() const {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << queue_[q_l_] << "\n";
  }

  void Clear() {
    q_l_ = q_r_ = 0;
    mn_l_ = mn_r_ = 0;
    std::cout << "ok\n";
  }

  void FindMin() const {
    if (Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << mins_[mn_l_] << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
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
