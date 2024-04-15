#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/interp_fps.hpp"

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
  u32 n;
  tifa_libs::fin >> n;
  poly a(n), b(n);
  tifa_libs::fin >> a.data() >> b.data();
  tifa_libs::fout << tifa_libs::math::interp_fps(a, b).data() << '\n';
  return 0;
}
