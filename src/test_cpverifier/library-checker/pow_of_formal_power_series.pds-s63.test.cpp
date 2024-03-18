#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s63.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_pow.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/io/fastio.hpp"

using mintdata = tifa_libs::math::mintdata_s63<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s<mint>>;

int main() {
  u32 n;
  u64 m;
  tifa_libs::fin >> n >> m;
  poly_t a(n);
  tifa_libs::fin >> a.data();
  tifa_libs::fout << tifa_libs::math::poly_pow(a, m).data() << '\n';
  return 0;
}
