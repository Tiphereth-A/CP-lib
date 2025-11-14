#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../include/math/fact_mint.hpp"

using namespace tifa_libs;
CEXP u64 MOD = 1000000007;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_sbrt.hpp"
#include "../../include/poly/polymtt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_sbrt, MOD>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::fact_mint<poly>(n) << '\n';
  return 0;
}
