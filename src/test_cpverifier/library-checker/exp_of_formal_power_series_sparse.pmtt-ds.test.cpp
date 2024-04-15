#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/exp_fpssp.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ds.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, k;
  tifa_libs::fin >> n >> k;
  poly p(n);
  for (u32 i = 0, x; i < k; ++i) tifa_libs::fin >> x >> p[x];
  tifa_libs::fout << tifa_libs::math::exp_fpssp(p).data();
  return 0;
}
