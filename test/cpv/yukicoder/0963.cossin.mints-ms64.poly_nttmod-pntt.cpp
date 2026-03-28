#define AUTO_GENERATED
#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../../src/fps/cossin/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1012924417;

#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using namespace tifa_libs;
using poly = polyntt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mint fact_n = 1;
  flt_ (u32, i, 1, n + 1) fact_n *= i;
  auto [fc, fs] = tifa_libs::cossin_fps(poly{0, 1}, n + 1);
  std::cout << ((fs + 1) * inv_fps(fc, n + 1))[n] * 2 * fact_n << '\n';
  return 0;
}
