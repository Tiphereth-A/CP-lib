// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include "../../../src/math/qpow/mod/lib.hpp"

using namespace tifa_libs;
CEXP i64 MOD = 1'000'000'007;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 m, n;
  std::cin >> m >> n;
  std::cout << qpow_mod(m, n, MOD) << '\n';
  return 0;
}
