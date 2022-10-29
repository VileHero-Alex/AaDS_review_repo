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
  long long* heap_;
  long long* req_to_pos_;
  long long* pos_to_req_;

  void SwapVertexes(long long ver1, long long ver2) {
    std::swap(heap_[ver1], heap_[ver2]);
    std::swap(req_to_pos_[pos_to_req_[ver1]], req_to_pos_[pos_to_req_[ver2]]);
    std::swap(pos_to_req_[ver1], pos_to_req_[ver2]);
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
  MyHeap(long long q) {
    heap_ = new long long[q];
    req_to_pos_ = new long long[q];
    pos_to_req_ = new long long[q];
  }
  ~MyHeap() {
    delete[] heap_;
    delete[] req_to_pos_;
    delete[] pos_to_req_;
  }

  void Insert(long long x, long long num) {
    heap_[size_heap_] = x;
    req_to_pos_[num] = size_heap_;
    pos_to_req_[size_heap_] = num;
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

  void DecreaseKey(long long query_num, long long delta) {
    long long pos_heap = req_to_pos_[query_num];
    heap_[pos_heap] -= delta;
    SiftUp(pos_heap);
  }
};

void Solve() {
  long long q;
  std::cin >> q;
  MyHeap box(q + 1000);
  for (long long i = 1; i <= q; ++i) {
    std::string t;
    std::cin >> t;
    if (t == "insert") {
      long long val;
      std::cin >> val;
      box.Insert(val, i);
    } else if (t == "getMin") {
      std::cout << box.CheckMin() << "\n";
    } else if (t == "extractMin") {
      box.ExtractMin();
    } else {
      long long num, delta;
      std::cin >> num >> delta;
      box.DecreaseKey(num, delta);
    }
  }
}

signed main() {
  SpeedUp();
  Solve();
  return 0;
}
