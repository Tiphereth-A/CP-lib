#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/comp_fpssps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d31.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using mint1 = tifa_libs::math::mint_s30<167772161>;
using mint2 = tifa_libs::math::mint_s30<469762049>;
using mint3 = tifa_libs::math::mint_s30<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  u32 m, n;
  tifa_libs::fin >> m >> n;
  poly a(m);
  tifa_libs::fin >> a.data();
  vec<mint> b(1 << n);
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::comp_fpssps(n, a, b) << '\n';
  return 0;
}
