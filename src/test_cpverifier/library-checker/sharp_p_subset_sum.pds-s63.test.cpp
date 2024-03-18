#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s63.hpp"
#include "../../code/math/ssts_pim_cnt.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/polydata_s.hpp"
#include "../../code/io/fastio.hpp"

using mintdata = tifa_libs::math::mintdata_s63<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
using pdata_t = tifa_libs::math::polydata_s<mint>;
using poly_t = tifa_libs::math::poly<pdata_t>;

int main() {
  u32 n, t;
  tifa_libs::fin >> n >> t;
  vec<u32> s(n);
  tifa_libs::fin >> s;
  auto v = tifa_libs::math::ssts_pim_cnt<pdata_t>(s, t).data();
  for (u32 i = 1; i <= t; ++i) tifa_libs::fout.write(v[i]).space_if(i != t);
  tifa_libs::fout.linebreak();
  return 0;
}
