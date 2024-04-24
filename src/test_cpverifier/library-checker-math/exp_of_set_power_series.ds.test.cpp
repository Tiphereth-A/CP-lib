#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/exp_fpssps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ds.hpp"

using mint = tifa_libs::math::mint_ds<-1>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin >> n;
  vec<mint> b(1 << n);
  tifa_libs::fin >> b;
  tifa_libs::fout << tifa_libs::math::exp_fpssps(n, b) << '\n';
  return 0;
}