#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include "../../code/math/qpow_mod.hpp"

CEXP i64 MOD = 1'000'000'007;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 m, n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow_mod(m, n, MOD) << '\n';
  return 0;
}
