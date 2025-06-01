#define AUTO_GENERATED
#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../include/poly/cossin_fps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1012924417;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/poly/polyntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;
using namespace tifa_libs;
using poly = math::polyntt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mint fact_n = 1;
  flt_ (u32, i, 1, n + 1) fact_n *= i;
  auto [fc, fs] = tifa_libs::math::cossin_fps(poly{0, 1}, n + 1);
  std::cout << ((fs + 1) * inv_fps(fc, n + 1))[n] * 2 * fact_n << '\n';
  return 0;
}
