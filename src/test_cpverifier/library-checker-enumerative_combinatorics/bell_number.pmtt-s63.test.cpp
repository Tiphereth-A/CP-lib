#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"

#include "../../code/comb/gen_bell.hpp"
#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  auto ans = tifa_libs::math::gen_bell<poly>(n);
  flt_ (u32, i, 0, n + 1) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
