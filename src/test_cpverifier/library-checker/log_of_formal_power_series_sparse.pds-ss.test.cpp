#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse"

#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/poly/polysp_ln.hpp"

using mdata = tifa_libs::math::mint_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using pldt_t = tifa_libs::math::polydata_s<mint>;
using poly_t = tifa_libs::math::poly<pldt_t>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  poly_t p(n);
  for (usz i = 0, x; i < k; ++i) std::cin >> x >> p[x];
  std::cout << tifa_libs::math::polysp_ln(p);
  return 0;
}
