#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../include/poly/ode_fps.hpp"

CEXP u32 MOD = 1012924417;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  auto g = [](poly CR f, u32 n) { return ((f * f + 1) * mint(2).inv()).pre(n); };
  auto dg = [](poly CR f, u32 n) { return f.pre(n); };
  mint ans = tifa_libs::math::ode_fps<poly>(g, dg, 1, n + 1)[n] * 2;
  flt_ (u32, i, 2, n + 1) ans *= i;
  std::cout << ans << '\n';
  return 0;
}
