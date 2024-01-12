#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_ln.hpp"
#include "../../code/poly/polydata_scntt.hpp"

using mdata = tifa_libs::math::mint_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_scntt<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  poly_t p(n);
  std::cin >> p;
  std::cout << tifa_libs::math::poly_ln(p);
  return 0;
}
