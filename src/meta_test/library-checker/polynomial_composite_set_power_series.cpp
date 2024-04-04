#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../code/io/ios_container.hpp"
#include "../../code/poly/comp_fpssps.hpp"

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
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 m, n;
  std::cin >> m >> n;
  poly a(m);
  std::cin >> a;
  vec<mint> b(1 << n);
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::comp_fpssps(n, a, b) << '\n';
  return 0;
}
