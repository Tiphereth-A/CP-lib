#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_sqrt.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s32<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  poly_t p(n);
  std::cin >> p;
  auto res = tifa_libs::math::poly_sqrt(p);
  if (!res.has_value()) std::cout << "-1\n";
  else std::cout << res.value() << '\n';
  return 0;
}
