#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "../../code/math/qresidue.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::i64 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::u64 y, p;
    std::cin >> y >> p;
    auto res = tifa_libs::math::qresidue(y, p);
    std::cout << (res ? res.value() : -1) << '\n';
  }
  return 0;
}
