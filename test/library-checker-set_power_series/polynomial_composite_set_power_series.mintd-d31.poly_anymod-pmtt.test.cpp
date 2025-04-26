#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/poly/comp_fpssps.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"
#include "../../include/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 m, n;
  tifa_libs::fin >> m >> n;
  poly a(m);
  tifa_libs::fin >> a;
  vec<mint> b(1 << n);
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::comp_fpssps(n, a, b) << '\n';
  return 0;
}
