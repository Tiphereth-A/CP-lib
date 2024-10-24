#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/poly/ode_fps.hpp"

CEXP u32 MOD = 1012924417;

#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  auto g = [](cT_(poly) f, u32 n) { return ((f * f + 1) * mint(2).inv()).pre(n); };
  auto dg = [](cT_(poly) f, u32 n) { return f.pre(n); };
  mint ans = tifa_libs::math::ode_fps<mint, TPN poly::ccore_t>(g, dg, 1, n + 1)[n] * 2;
  fle_(u32, i, 2, n) ans *= i;
  std::cout << ans << '\n';
  return 0;
}
