#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

class SegmentTree {
 private:
  int sz_;
  std::vector<int> tree_;

  int GetResOnSegment(int v, int l, int r, int val);
  int GetAnswerForQueryDeveloperVersion(int ql, int val, int v,
                                        std::pair<int, int> borders, int qr);
  void UpdateDeveloperVersion(int v, int l, int r, int pos, int val);
  void Build(int v, int l, int r, const std::vector<int>& a);

 public:
  static const int kINF = static_cast<int>(1e9);

  SegmentTree(int n, const std::vector<int>& arr)
      : sz_(n), tree_((std::__lg(n) + 1) * n) {
    Build(1, 0, n, arr);
  }
  void Update(int pos, int val);
  int GetAnswerForQuery(int ql, int val);
};

void Solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  SegmentTree tree(n, arr);
  for (int i = 0; i < m; ++i) {
    int t, pos, x;
    std::cin >> t >> pos >> x;
    --pos;
    if (t == 0) {
      tree.Update(pos, x);
    } else {
      int ans = tree.GetAnswerForQuery(pos, x);
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

int SegmentTree::GetResOnSegment(int v, int l, int r, int val) {
  if (tree_[v] < val) {
    return -kINF;
  }
  if (l + 1 == r) {
    return l;
  }
  int md = (l + r) / 2;
  if (tree_[2 * v] >= val) {
    return GetResOnSegment(2 * v, l, md, val);
  }
  return GetResOnSegment(2 * v + 1, md, r, val);
}

void SegmentTree::Build(int v, int l, int r, const std::vector<int>& a) {
  if (l + 1 == r) {
    tree_[v] = a[l];
    return;
  }
  int md = (l + r) / 2;
  Build(v * 2, l, md, a);
  Build(v * 2 + 1, md, r, a);
  tree_[v] = std::max(tree_[2 * v], tree_[2 * v + 1]);
}

void SegmentTree::Update(int pos, int val) {
  UpdateDeveloperVersion(1, 0, sz_, pos, val);
}

void SegmentTree::UpdateDeveloperVersion(int v, int l, int r, int pos,
                                         int val) {
  if (l + 1 == r) {
    tree_[v] = val;
    return;
  }
  int md = (l + r) / 2;
  if (pos < md) {
    UpdateDeveloperVersion(2 * v, l, md, pos, val);
  } else {
    UpdateDeveloperVersion(2 * v + 1, md, r, pos, val);
  }
  tree_[v] = std::max(tree_[2 * v], tree_[2 * v + 1]);
}

int SegmentTree::GetAnswerForQuery(int ql, int val) {
  return GetAnswerForQueryDeveloperVersion(ql, val, 1, {0, sz_}, sz_);
}

int SegmentTree::GetAnswerForQueryDeveloperVersion(int ql, int val, int v,
                                                   std::pair<int, int> borders,
                                                   int qr) {
  int l = borders.first, r = borders.second;
  if (ql == l && qr == r) {
    return GetResOnSegment(v, l, r, val);
  }
  int md = (l + r) / 2;
  if (ql < md) {
    int res = GetAnswerForQueryDeveloperVersion(ql, val, 2 * v, {l, md},
                                                std::min(qr, md));
    if (res != -kINF) {
      return res;
    }
  }
  if (qr > md) {
    int res = GetAnswerForQueryDeveloperVersion(std::max(ql, md), val,
                                                2 * v + 1, {md, r}, qr);
    return res;
  }
  return -kINF;
}
