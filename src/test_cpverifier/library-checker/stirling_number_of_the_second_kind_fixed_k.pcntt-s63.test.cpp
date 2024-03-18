#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_fixed_k"

#include "../../code/comb/gen_stirling2_col.hpp"
#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  u32 n, k;
  tifa_libs::fin >> n >> k;
  auto ans = tifa_libs::math::gen_stirling2_col<poly>(n, k);
  for (usz i = k; i <= n; ++i) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
