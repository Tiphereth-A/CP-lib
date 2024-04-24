#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "../../code/nt/qresidue.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 y, p;
    std::cin >> y >> p;
    auto res = tifa_libs::math::qresidue(y, p);
    std::cout << (res ? (i64)res.value() : -1) << '\n';
  }
  return 0;
}
