#include <iostream>
#include <vector>

void SpeedUp() {
  std::cin.tie(0);
  std::cout.tie(0);
  std::ios_base::sync_with_stdio(false);
}

class MyHashTable {
 private:
  size_t sz_ = 1;
  std::vector<std::vector<long long>> table_;
  long long cnt_ = 0;
  double RaiseConst_ = 0.75;
  const long long kConstForHash = 838383, kModForHash = 200720072;

 public:
  MyHashTable() : table_(sz_) {}

  void Raisecnt() {
    ++cnt_;
    if (static_cast<double>(cnt_) / static_cast<double>(sz_) >= RaiseConst_) {
      sz_ *= 2;
      std::vector<std::vector<long long>> temp(sz_);
      for (size_t i = 0; i < (sz_ / 2); ++i) {
        for (size_t j = 0; j < table_[i].size(); ++j) {
          long long x = table_[i][j];
          int new_hash = GetHash(x) % sz_;
          temp[new_hash].push_back(x);
        }
      }
      swap(temp, table_);
    }
  }

  int GetHash(long long x) { return (x * kConstForHash) % kModForHash; }

  void Insert(long long x) {
    if (Find(x)) {
      return;
    }
    Raisecnt();
    int res = GetHash(x) % sz_;
    table_[res].push_back(x);
  }

  bool Find(long long x) {
    int res = GetHash(x) % sz_;
    for (size_t i = 0; i < table_[res].size(); ++i) {
      if (table_[res][i] == x) {
        return true;
      }
    }
    return false;
  }

  void Delete(long long x) {
    if (!Find(x)) {
      return;
    }
    int res = GetHash(x) % sz_;
    size_t pos;
    for (pos = 0; pos < table_[res].size(); ++pos) {
      if (table_[res][pos] == x) {
        break;
      }
    }
    std::swap(table_[res][pos], table_[res][table_[res].size() - 1]);
    table_[res].pop_back();
  }
};

void Solve() {
  int q;
  std::cin >> q;
  MyHashTable box;
  for (int i = 0; i < q; ++i) {
    char t;
    long long x;
    std::cin >> t >> x;
    if (t == '+') {
      box.Insert(x);
    } else if (t == '-') {
      box.Delete(x);
    } else {
      box.Find(x) ? std::cout << "YES\n" : std::cout << "NO\n";
    }
  }
}

signed main() {
  SpeedUp();
  Solve();
  return 0;
}
