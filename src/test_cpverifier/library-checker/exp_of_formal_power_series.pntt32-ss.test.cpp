#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly_exp.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly p(n);
  for (auto& i : p.data()) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::poly_exp(p).data();
  return 0;
}
