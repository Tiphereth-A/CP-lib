#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"

#include "../../code/comb/gen_bell.hpp"
#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 998244353;

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
  u32 n;
  tifa_libs::fin >> n;
  auto ans = tifa_libs::math::gen_bell<poly>(n);
  fle_ (u32, i, 0, n) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
