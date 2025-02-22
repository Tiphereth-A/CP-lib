#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/poly/comp_fpssps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 m, n;
  tifa_libs::fin >> m >> n;
  poly a(m);
  tifa_libs::fin >> a;
  vec<mint> b(1 << n);
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::comp_fpssps(n, a, b) << '\n';
  return 0;
}
