#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polyntt32.hpp"
#include "../../code/poly/polysp_exp.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  poly p(n);
  for (u32 i = 0, x; i < k; ++i) std::cin >> x >> p[x];
  std::cout << tifa_libs::math::polysp_exp(p);
  return 0;
}
