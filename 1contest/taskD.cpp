#include <algorithm>
#include <deque>
#include <iostream>

struct SuperQueue {
  std::deque<int> fr, bck;
  SuperQueue() {}
  void CheckAmount() {
    while (fr.size() < bck.size()) {
      int cur = bck.front();
      bck.pop_front();
      fr.push_back(cur);
    }
  }
  void PushLast(int val) {
    CheckAmount();
    bck.push_back(val);
    CheckAmount();
  }
  void PushMiddle(int val) {
    CheckAmount();
    if (fr.size() == bck.size()) {
      fr.push_back(val);
    } else {
      bck.push_front(val);
    }
    CheckAmount();
  }
};

int main() {
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  SuperQueue curr_queue;
  for (int q = 0; q < n; ++q) {
    char v;
    std::cin >> v;
    if (v == '-') {
      int ans = curr_queue.fr.front();
      curr_queue.fr.pop_front();
      curr_queue.CheckAmount();
      std::cout << ans << "\n";
    } else {
      int num;
      std::cin >> num;
      if (v == '*') {
        curr_queue.PushMiddle(num);
      } else {
        curr_queue.PushLast(num);
      }
    }
  }
}
