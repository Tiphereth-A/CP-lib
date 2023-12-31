#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_pow.hpp"
#include "../../code/poly/polydata_scntt.hpp"
#include "../../code/util/fastio.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_scntt<mint>>;

int main() {
  u32 n;
  u64 m;
  tifa_libs::fin >> n >> m;
  poly_t a(n);
  tifa_libs::fin >> a.data();
  tifa_libs::fout << tifa_libs::math::poly_pow(a, m).data() << '\n';
  return 0;
}
