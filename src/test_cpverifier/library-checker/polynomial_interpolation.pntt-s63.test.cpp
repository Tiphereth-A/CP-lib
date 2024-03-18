#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly_interp.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  poly a(n), b(n);
  std::cin >> a >> b;
  std::cout << tifa_libs::math::poly_interp(a, b) << '\n';
  return 0;
}
