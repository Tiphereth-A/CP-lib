#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/poly/poly_ode.hpp"

constexpr u32 MOD = 1012924417;

#define GENTCs_p3ntts
#define GENTCs_p3nttd0
#define GENTCs_pmtts
#define GENTCs_pmttd0
#define GENTCs_pntt

int main() {
#define GENTCs_p3nttd1
#define GENTCs_pmttd1
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  auto g = [](poly const& f, u32 n) { return ((f * f + 1) * mint(2).inv()).pre(n); };
  auto dg = [](poly const& f, u32 n) { return f.pre(n); };
  mint ans = tifa_libs::math::poly_ode<poly>(g, dg, 1, n + 1)[n] * 2;
  for (u32 i = 2; i <= n; ++i) ans *= i;
  std::cout << ans << '\n';
  return 0;
}
