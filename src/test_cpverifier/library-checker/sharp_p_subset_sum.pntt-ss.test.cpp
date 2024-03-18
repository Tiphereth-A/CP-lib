#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/math/ssts_pim_cnt.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using poly = tifa_libs::math::polyntt<mint>;

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
