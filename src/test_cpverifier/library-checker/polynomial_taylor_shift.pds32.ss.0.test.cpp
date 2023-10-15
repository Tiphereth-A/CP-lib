#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_tsh.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using polyd = tifa_libs::math::polydata_s32<mint>;
using poly_t = tifa_libs::math::poly<polyd>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, c;
  std::cin >> n >> c;
  poly_t a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::poly_tsh<polyd>(a, c) << '\n';
  return 0;
}
