#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_fixed_k"

#include "../../code/comb/gen_stirling1_col.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/util/fastio.hpp"

using mdata = tifa_libs::math::mdata_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using polyd = tifa_libs::math::polydata_s<mint>;

int main() {
  u32 n, k;
  tifa_libs::fin >> n >> k;
  auto ans = tifa_libs::math::gen_stirling1_col<polyd>(n, k);
  for (usz i = k; i <= n; ++i) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
