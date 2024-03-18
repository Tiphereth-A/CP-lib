#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly_interp.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using poly = tifa_libs::math::polyntt32<mint>;

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
