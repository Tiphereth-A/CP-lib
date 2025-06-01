#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../include/math/fact_mint.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/poly/polymtt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, MOD>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u64 n;
    std::cin >> n;
    std::cout << tifa_libs::math::fact_mint<poly>(n) << '\n';
  }
  return 0;
}
