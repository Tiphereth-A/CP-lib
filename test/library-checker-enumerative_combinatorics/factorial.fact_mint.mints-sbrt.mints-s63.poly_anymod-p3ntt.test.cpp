#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../include/math/fact_mint.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/math/mint_sbrt.hpp"
#include "../../include/poly/poly3ntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_sbrt, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_s63, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_s63, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_s63, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

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
