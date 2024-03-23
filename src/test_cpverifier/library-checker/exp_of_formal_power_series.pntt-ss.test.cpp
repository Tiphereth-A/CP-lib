#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/poly_exp.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly p(n);
  tifa_libs::fin >> p.data();
  tifa_libs::fout << tifa_libs::math::poly_exp(p).data();
  return 0;
}
