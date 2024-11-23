#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/poly/ode_fps.hpp"

CEXP u32 MOD = 1012924417;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d63.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using mint1 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 167772161>;
using mint2 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 469762049>;
using mint3 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
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
