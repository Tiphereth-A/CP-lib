#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/mpe_fps.hpp"

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
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly a(n), p(m);
  tifa_libs::fin >> a.data() >> p.data();
  tifa_libs::fout << tifa_libs::math::mpe_fps(a, p).data() << '\n';
  return 0;
}
