#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_sqrt.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/util/fastio.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s<mint>>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly_t p(n);
  tifa_libs::fin >> p.data();
  auto res = tifa_libs::math::poly_sqrt(p);
  if (!res.has_value()) tifa_libs::fout << "-1\n";
  else tifa_libs::fout << res.value().data() << '\n';
  return 0;
}
