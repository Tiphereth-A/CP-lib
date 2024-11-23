#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/inv_fpssp.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using mint1 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 167772161>;
using mint2 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 469762049>;
using mint3 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  u32 n, k;
  tifa_libs::fin >> n >> k;
  poly p(n);
  for (u32 i = 0, x; i < k; ++i) tifa_libs::fin >> x >> p[x];
  tifa_libs::fout << tifa_libs::math::inv_fpssp(p);
  return 0;
}
