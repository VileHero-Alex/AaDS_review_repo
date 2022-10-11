#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  long double* a = new long double[3 * (int)1e5 + 100];
  long double* pref = new long double[3 * (int)1e5 + 100];
  pref[0] = 0;
  int n, q;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    pref[i + 1] = pref[i] + log2(a[i]);
  }
  std::cin >> q;
  for (int qr = 0; qr < q; ++qr) {
    int l, r;
    std::cin >> l >> r;
    std::cout << std::setprecision(10)
              << pow((long double)2, (pref[r + 1] - pref[l]) /
                                         ((long double)r + 1 - (long double)l))
              << "\n";
  }
  delete[] a;
  delete[] pref;
}
