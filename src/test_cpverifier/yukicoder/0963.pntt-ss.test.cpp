#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/poly/poly_ode.hpp"

constexpr u32 MOD = 1012924417;

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
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
