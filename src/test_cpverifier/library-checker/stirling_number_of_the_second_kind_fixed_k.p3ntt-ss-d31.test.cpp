#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_fixed_k"

#include "../../code/comb/gen_stirling2_col.hpp"
#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d31.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using mint1 = tifa_libs::math::mint_ss<167772161>;
using mint2 = tifa_libs::math::mint_ss<469762049>;
using mint3 = tifa_libs::math::mint_ss<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  u32 n, k;
  tifa_libs::fin >> n >> k;
  auto ans = tifa_libs::math::gen_stirling2_col<poly>(n, k);
  for (usz i = k; i <= n; ++i) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
