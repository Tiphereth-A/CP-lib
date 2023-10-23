#define PROBLEM "https://www.luogu.com.cn/problem/P5396"

#include "../../code/comb/stirling2_col_gen.hpp"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mint = tifa_libs::math::mint_s30<167772161>;
using polyd = tifa_libs::math::polydata_s32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  auto ans = tifa_libs::math::stirling2_col_gen<polyd>(n, k);
  for (usz i = 0; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];
  return 0;
}
