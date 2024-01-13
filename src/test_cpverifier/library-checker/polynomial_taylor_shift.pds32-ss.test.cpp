#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../code/math/mintdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_tsh.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mintdata = tifa_libs::math::mintdata_ss<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
using polyd = tifa_libs::math::polydata_s32<mint>;
using poly_t = tifa_libs::math::poly<polyd>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, c;
  std::cin >> n >> c;
  poly_t a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::poly_tsh<polyd>(a, c) << '\n';
  return 0;
}
