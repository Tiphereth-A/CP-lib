#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/poly/exp_fpssps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  vec<mint> b(1 << n);
  tifa_libs::fin >> b;
  tifa_libs::fout << tifa_libs::math::exp_fpssps(n, b) << '\n';
  return 0;
}
