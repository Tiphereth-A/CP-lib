#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/poly/pow_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  u64 m;
  tifa_libs::fin >> n >> m;
  poly a(n);
  tifa_libs::fin >> a;
  tifa_libs::fout << tifa_libs::math::pow_fps(a, m) << '\n';
  return 0;
}
