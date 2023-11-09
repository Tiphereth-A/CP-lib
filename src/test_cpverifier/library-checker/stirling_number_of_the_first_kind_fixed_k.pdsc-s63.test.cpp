#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_fixed_k"

#include "../../code/comb/gen_stirling1_col.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polydata_scntt.hpp"
#include "../../code/util/fastio.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using polyd = tifa_libs::math::polydata_scntt<mint>;

int main() {
  u32 n, k;
  tifa_libs::fin >> n >> k;
  auto ans = tifa_libs::math::gen_stirling1_col<polyd>(n, k);
  for (usz i = k; i <= n; ++i) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
