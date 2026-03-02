#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"

#include "../../../src/comb/ball_box/idm/lib.hpp"
#include "../../../src/comb/binom/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_bs, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_bs, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_bs, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;
using namespace tifa_libs;
using fact_t = math::factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::math::binom<mint, fact_t> binom(2001);
  std::cout << tifa_libs::math::ball_box_idm<mint>(n, k, binom) << '\n';
  return 0;
}
