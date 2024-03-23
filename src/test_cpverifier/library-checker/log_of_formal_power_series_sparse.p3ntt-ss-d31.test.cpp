#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse"

#include "../../code/poly/polysp_ln.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d31.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using mint1 = tifa_libs::math::mint_ss<167772161>;
using mint2 = tifa_libs::math::mint_ss<469762049>;
using mint3 = tifa_libs::math::mint_ss<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  poly p(n);
  for (usz i = 0, x; i < k; ++i) std::cin >> x >> p[x];
  std::cout << tifa_libs::math::polysp_ln(p);
  return 0;
}
