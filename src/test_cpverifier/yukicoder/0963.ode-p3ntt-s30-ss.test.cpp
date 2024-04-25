#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/poly/ode_fps.hpp"

CEXP u32 MOD = 1012924417;

#include "../../code/math/mint_s30.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using mint1 = tifa_libs::math::mint_s30<167772161>;
using mint2 = tifa_libs::math::mint_s30<469762049>;
using mint3 = tifa_libs::math::mint_s30<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  auto g = [](cT_(poly) f, u32 n) { return ((f * f + 1) * mint(2).inv()).pre(n); };
  auto dg = [](cT_(poly) f, u32 n) { return f.pre(n); };
  mint ans = tifa_libs::math::ode_fps<mint, TPN poly::ccore_type>(g, dg, 1, n + 1)[n] * 2;
  fle_(u32, i, 2, n) ans *= i;
  std::cout << ans << '\n';
  return 0;
}
