#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/comp_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly g(n), f(n);
  tifa_libs::fin >> g.data() >> f.data();
  tifa_libs::fout << tifa_libs::math::comp_fps(f, g).data();
  return 0;
}