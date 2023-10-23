#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../../code/math/exbsgs.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 x, y, m;
    std::cin >> x >> y >> m;
    auto res = tifa_libs::math::exbsgs(x, y, m);
    std::cout << (res ? (i64)res.value() : -1) << '\n';
  }
  return 0;
}
