#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/poly/polysp_inv.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using pldt_t = tifa_libs::math::polydata_s<mint>;
using poly_t = tifa_libs::math::poly<pldt_t>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, k;
  std::cin >> n >> k;
  poly_t p(n);
  for (size_t i = 0, x; i < k; ++i) std::cin >> x >> p[x];
  std::cout << tifa_libs::math::polysp_inv(p);
  return 0;
}
