#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly_ode.hpp"
#include "../../code/poly/polydata_s.hpp"

using mint = tifa_libs::math::mint_s30<1012924417>;
using pldt_t = tifa_libs::math::polydata_s<mint>;
using poly_t = tifa_libs::math::poly<pldt_t>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n;
  std::cin >> n;
  auto g = [](poly_t const& f, size_t n) { return ((f * f + 1) * mint(2).inv()).pre(n); };
  auto dg = [](poly_t const& f, size_t n) { return f.pre(n); };
  mint ans = tifa_libs::math::poly_ode<pldt_t>(g, dg, 1, n + 1)[n] * 2;
  for (size_t i = 2; i <= n; ++i) ans *= i;
  std::cout << ans;
  return 0;
}
