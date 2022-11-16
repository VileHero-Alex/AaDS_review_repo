#include <iostream>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

class SegmentTree {
 private:
  int* tree_;

 public:
  const int kINF = static_cast<int>(1e9);

  SegmentTree(int sz) { tree_ = new int[sz * 5]; }
  ~SegmentTree() { delete[] tree_; }

  void Build(int v, int l, int r, const std::vector<int>& a) {
    if (l + 1 == r) {
      tree_[v] = a[l];
      return;
    }
    int md = (l + r) / 2;
    Build(v * 2, l, md, a);
    Build(v * 2 + 1, md, r, a);
    tree_[v] = std::max(tree_[2 * v], tree_[2 * v + 1]);
  }

  void Update(int v, int l, int r, int pos, int val) {
    if (l + 1 == r) {
      tree_[v] = val;
      return;
    }
    int md = (l + r) / 2;
    if (pos < md) {
      Update(2 * v, l, md, pos, val);
    } else {
      Update(2 * v + 1, md, r, pos, val);
    }
    tree_[v] = std::max(tree_[2 * v], tree_[2 * v + 1]);
  }

  int GetRes(int v, int l, int r, int val) {
    if (tree_[v] < val) {
      return -kINF;
    }
    if (l + 1 == r) {
      return l;
    }
    int md = (l + r) / 2;
    if (tree_[2 * v] >= val) {
      return GetRes(2 * v, l, md, val);
    }
    return GetRes(2 * v + 1, md, r, val);
  }

  int GetCover(int v, int l, int r, std::pair<int, int> query, int val) {
    int ql = query.first, qr = query.second;
    if (ql == l && qr == r) {
      return GetRes(v, l, r, val);
    }
    int md = (l + r) / 2;
    if (ql < md) {
      int res = GetCover(2 * v, l, md, {ql, std::min(qr, md)}, val);
      if (res != -kINF) {
        return res;
      }
    }
    if (qr > md) {
      int res = GetCover(2 * v + 1, md, r, {std::max(ql, md), qr}, val);
      return res;
    }
    return -kINF;
  }
};

void Solve() {
  int n, m;
  std::cin >> n >> m;
  SegmentTree tree(n);
  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  tree.Build(1, 0, n, arr);
  for (int i = 0; i < m; ++i) {
    int t, pos, x;
    std::cin >> t >> pos >> x;
    --pos;
    if (t == 0) {
      tree.Update(1, 0, n, pos, x);
    } else {
      int ans = tree.GetCover(1, 0, n, {pos, n}, x);
      if (ans == -tree.kINF) {
        std::cout << "-1\n";
      } else {
        std::cout << ans + 1 << "\n";
      }
    }
  }
}

int main() {
  SpeedUp();
  Solve();
  return 0;
}
