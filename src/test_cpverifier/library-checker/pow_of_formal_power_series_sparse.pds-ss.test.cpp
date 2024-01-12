#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse"

#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/poly/polysp_pow.hpp"

using mdata = tifa_libs::math::mdata_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using pldt_t = tifa_libs::math::polydata_s<mint>;
using poly_t = tifa_libs::math::poly<pldt_t>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  u64 m;
  std::cin >> n >> k >> m;
  poly_t p(n);
  for (u32 i = 0, x; i < k; ++i) std::cin >> x >> p[x];
  std::cout << tifa_libs::math::polysp_pow(p, m);
  return 0;
}
