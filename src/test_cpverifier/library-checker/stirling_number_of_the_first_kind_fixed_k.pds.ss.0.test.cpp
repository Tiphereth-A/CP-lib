#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_fixed_k"

#include "../../code/comb/stirling1_col_gen.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polydata_s.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using polyd = tifa_libs::math::polydata_s<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  auto ans = tifa_libs::math::stirling1_col_gen<polyd>(n, k);
  for (size_t i = k; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];
  return 0;
}
