#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_interp.hpp"
#include "../../code/poly/polydata_s.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  poly_t a(n), b(n);
  std::cin >> a >> b;
  auto c = tifa_libs::math::poly_interp(a, b);
  for (size_t i = 0; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
