#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_fixed_k"

#include "../../include/comb/gen_stirling2_col.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  u32 n, k;
  tifa_libs::fin >> n >> k;
  auto ans = tifa_libs::math::gen_stirling2_col<poly>(n, k);
  flt_ (u32, i, k, n + 1) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
