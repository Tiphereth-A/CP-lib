#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/pow_fpssp.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n, k;
  u64 m;
  tifa_libs::fin >> n >> k >> m;
  poly p(n);
  for (u32 i = 0, x; i < k; ++i) tifa_libs::fin >> x >> p[x];
  tifa_libs::fout << tifa_libs::math::pow_fpssp(p, m).data();
  return 0;
}
