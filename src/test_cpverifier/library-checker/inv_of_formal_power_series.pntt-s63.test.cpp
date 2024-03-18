#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly_inv.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly p(n);
  tifa_libs::fin >> p.data();
  tifa_libs::fout << tifa_libs::math::poly_inv(p).data();
  return 0;
}
