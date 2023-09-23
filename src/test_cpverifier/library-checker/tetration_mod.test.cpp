#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"

#include "../../code/math/qtetra_mod.hpp"

int main() {
  tifa_libs::i64 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::u64 a, b, m;
    std::cin >> a >> b >> m;
    std::cout << tifa_libs::math::qtetra_mod(a, b, m) << '\n';
  }
  return 0;
}
