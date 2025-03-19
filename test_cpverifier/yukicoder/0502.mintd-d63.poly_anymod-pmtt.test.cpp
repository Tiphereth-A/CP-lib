#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../include/math/fact_mint.hpp"

CEXP u64 MOD = 1000000007;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d63.hpp"
#include "../../include/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::fact_mint<poly>(n) << '\n';
  return 0;
}
