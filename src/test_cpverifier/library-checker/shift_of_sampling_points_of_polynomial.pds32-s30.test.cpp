#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s30.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_ctsh.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mintdata = tifa_libs::math::mintdata_s30<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
using polyd = tifa_libs::math::polydata_s32<mint>;
using poly_t = tifa_libs::math::poly<polyd>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, c;
  std::cin >> n >> m >> c;
  poly_t a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::poly_ctsh<polyd>(a, c, m) << '\n';
  return 0;
}
