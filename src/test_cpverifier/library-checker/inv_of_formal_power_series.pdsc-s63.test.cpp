#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_inv.hpp"
#include "../../code/poly/polydata_scntt.hpp"
#include "../../code/util/fastio.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_scntt<mint>>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly_t p(n);
  tifa_libs::fin >> p.data();
  tifa_libs::fout << tifa_libs::math::poly_inv(p).data();
  return 0;
}
