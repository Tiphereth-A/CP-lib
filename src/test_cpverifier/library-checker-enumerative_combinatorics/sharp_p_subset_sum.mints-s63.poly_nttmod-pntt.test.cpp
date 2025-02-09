#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../../code/io/fastio.hpp"
#include "../../code/math/ssts_pim_cnt.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n, t;
  tifa_libs::fin >> n >> t;
  vecu s(n);
  tifa_libs::fin >> s;
  auto v = tifa_libs::math::ssts_pim_cnt<poly>(s, t);
  flt_ (u32, i, 1, t + 1) tifa_libs::fout.write(v[i]).space_if(i != t);
  tifa_libs::fout.linebreak();
  return 0;
}
