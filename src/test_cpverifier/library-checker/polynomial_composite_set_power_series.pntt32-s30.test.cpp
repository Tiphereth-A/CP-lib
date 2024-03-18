#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polyntt32.hpp"
#include "../../code/poly/polysps_comp.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 m, n;
  std::cin >> m >> n;
  poly a(m);
  std::cin >> a;
  vec<mint> b(1 << n);
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::polysps_comp(n, a, b) << '\n';
  return 0;
}
