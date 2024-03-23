#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse"

#include "../../code/poly/polysp_exp.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using mint1 = tifa_libs::math::mint_s30<167772161>;
using mint2 = tifa_libs::math::mint_s30<469762049>;
using mint3 = tifa_libs::math::mint_s30<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

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
