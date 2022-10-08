#include <algorithm>
#include <deque>
#include <iostream>

std::deque<int> fr, bck;

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

int main() {
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  for (int q = 0; q < n; ++q) {
    char v;
    std::cin >> v;
    if (v == '-') {
      int ans = fr.front();
      fr.pop_front();
      CheckAmount();
      std::cout << ans << "\n";
    } else {
      int num;
      std::cin >> num;
      if (v == '*') {
        PushMiddle(num);
      } else {
        PushLast(num);
      }
    }
  }
}
