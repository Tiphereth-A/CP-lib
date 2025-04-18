#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../include/math/fact_mint.hpp"

CEXP u64 MOD = 1000000007;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d63.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using mint_p3ntt1 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 167772161>;
using mint_p3ntt2 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 469762049>;
using mint_p3ntt3 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::fact_mint<poly>(n) << '\n';
  return 0;
}
