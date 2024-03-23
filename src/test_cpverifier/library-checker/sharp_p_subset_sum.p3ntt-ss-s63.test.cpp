#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../../code/io/fastio.hpp"
#include "../../code/math/ssts_pim_cnt.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using mint1 = tifa_libs::math::mint_ss<167772161>;
using mint2 = tifa_libs::math::mint_ss<469762049>;
using mint3 = tifa_libs::math::mint_ss<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  u32 n, t;
  tifa_libs::fin >> n >> t;
  vec<u32> s(n);
  tifa_libs::fin >> s;
  auto v = tifa_libs::math::ssts_pim_cnt<poly>(s, t).data();
  for (u32 i = 1; i <= t; ++i) tifa_libs::fout.write(v[i]).space_if(i != t);
  tifa_libs::fout.linebreak();
  return 0;
}
