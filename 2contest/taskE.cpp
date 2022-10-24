#include <iostream>
#include <vector>

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

class MyHeap {
 private:
  long long size_heap_ = 0;
  const long long kSizeBox = 2 * (long long)1e5 + 100;
  long long* heap_;

  void SwapVertexes(long long ver1, long long ver2) {
    std::swap(heap_[ver1], heap_[ver2]);
  }

  void SiftUp(long long v) {
    while (v != 0) {
      if (heap_[v] < heap_[(v - 1) / 2]) {
        SwapVertexes(v, (v - 1) / 2);
        v = (v - 1) / 2;
      } else {
        break;
      }
    }
  }

  void SiftDown(long long v) {
    while (2 * v + 1 < size_heap_) {
      long long u = 2 * v + 1;
      if (2 * v + 2 < size_heap_ && heap_[2 * v + 2] < heap_[2 * v + 1]) {
        u = 2 * v + 2;
      }
      if (heap_[u] < heap_[v]) {
        SwapVertexes(v, u);
        v = u;
      } else {
        break;
      }
    }
  }

 public:
  MyHeap() { heap_ = new long long[kSizeBox]; }
  ~MyHeap() { delete[] heap_; }

  void Insert(long long x) {
    heap_[size_heap_] = x;
    ++size_heap_;
    SiftUp(size_heap_ - 1);
  }

  void ExtractMin() {
    SwapVertexes(0, size_heap_ - 1);
    --size_heap_;
    if (size_heap_ == 0) {
      return;
    }
    SiftDown(0);
  }

  long long CheckMin() const { return heap_[0]; }

  long long Size() const { return size_heap_; }

  void Clear() { size_heap_ = 0; }
};

void ClearingRubbish(long long x, MyHeap& box_min, MyHeap& box_max,
                     MyHeap& del_min, MyHeap& del_max) {
  del_min.Insert(x);
  del_max.Insert(-x);
  while (box_min.Size() > 0 && del_min.Size() > 0 &&
         del_min.CheckMin() == box_min.CheckMin()) {
    del_min.ExtractMin();
    box_min.ExtractMin();
  }
  while (box_max.Size() > 0 && del_max.Size() > 0 &&
         del_max.CheckMin() == box_max.CheckMin()) {
    del_max.ExtractMin();
    box_max.ExtractMin();
  }
}

void ClearingAll(MyHeap& box_min, MyHeap& box_max, MyHeap& del_min,
                 MyHeap& del_max) {
  box_min.Clear();
  box_max.Clear();
  del_min.Clear();
  del_max.Clear();
}

void Solve() {
  MyHeap box_min, box_max, del_min, del_max;
  long long q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string t;
    std::cin >> t;
    if (t == "insert") {
      long long x;
      std::cin >> x;
      std::cout << "ok\n";
      box_min.Insert(x);
      box_max.Insert(-x);
    } else if (t == "extract_min") {
      if (box_min.Size() == 0) {
        std::cout << "error\n";
        continue;
      }
      std::cout << box_min.CheckMin() << "\n";
      ClearingRubbish(box_min.CheckMin(), box_min, box_max, del_min, del_max);
    } else if (t == "get_min") {
      if (box_min.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << box_min.CheckMin() << "\n";
      }
    } else if (t == "extract_max") {
      if (box_max.Size() == 0) {
        std::cout << "error\n";
        continue;
      }
      std::cout << -box_max.CheckMin() << "\n";
      ClearingRubbish(-box_max.CheckMin(), box_min, box_max, del_min, del_max);
    } else if (t == "get_max") {
      if (box_max.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << -box_max.CheckMin() << "\n";
      }
    } else if (t == "size") {
      std::cout << box_max.Size() - del_max.Size() << "\n";
    } else {
      std::cout << "ok\n";
      ClearingAll(box_min, box_max, del_min, del_max);
    }
  }
}

signed main() {
  SpeedUp();
  Solve();
  return 0;
}
