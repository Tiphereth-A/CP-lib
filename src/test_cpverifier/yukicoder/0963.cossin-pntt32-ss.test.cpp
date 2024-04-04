#define AUTO_GENERATED
#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/poly/cossin_fps.hpp"

constexpr u32 MOD = 1012924417;

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  mint fact_n = 1;
  for (u32 i = 1; i <= n; ++i) fact_n *= i;
  auto [fc, fs] = tifa_libs::math::cossin_fps(poly{0, 1}, n + 1);
  std::cout << ((fs + 1) * inv_fps(fc, n + 1))[n] * 2 * fact_n << '\n';
  return 0;
}
