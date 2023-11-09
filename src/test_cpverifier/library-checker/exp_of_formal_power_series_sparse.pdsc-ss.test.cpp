#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse"

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polydata_scntt.hpp"
#include "../../code/poly/polysp_exp.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using pldt_t = tifa_libs::math::polydata_scntt<mint>;
using poly_t = tifa_libs::math::poly<pldt_t>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  poly_t p(n);
  for (usz i = 0, x; i < k; ++i) std::cin >> x >> p[x];
  std::cout << tifa_libs::math::polysp_exp(p);
  return 0;
}
