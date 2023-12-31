#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/poly/polysps_comp.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 m, n;
  std::cin >> m >> n;
  poly_t a(m);
  std::cin >> a;
  vec<mint> b(1 << n);
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::polysps_comp(n, a, b) << '\n';
  return 0;
}
