#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../../code/io/fastio.hpp"
#include "../../code/math/ssts_pim_cnt.hpp"

constexpr u32 MOD = 998244353;

#define GENTCs_p3ntts
#define GENTCs_p3nttd0
#define GENTCs_pcntts
#define GENTCs_pmtts
#define GENTCs_pmttd0
#define GENTCs_pntt

int main() {
#define GENTCs_p3nttd1
#define GENTCs_pmttd1
  u32 n, t;
  tifa_libs::fin >> n >> t;
  vecu s(n);
  tifa_libs::fin >> s;
  auto v = tifa_libs::math::ssts_pim_cnt<poly>(s, t).data();
  for (u32 i = 1; i <= t; ++i) tifa_libs::fout.write(v[i]).space_if(i != t);
  tifa_libs::fout.linebreak();
  return 0;
}
