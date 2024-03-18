#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse"

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polyntt.hpp"
#include "../../code/poly/polysp_ln.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  poly p(n);
  for (usz i = 0, x; i < k; ++i) std::cin >> x >> p[x];
  std::cout << tifa_libs::math::polysp_ln(p);
  return 0;
}
