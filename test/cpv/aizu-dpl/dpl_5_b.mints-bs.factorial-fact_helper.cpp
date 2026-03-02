#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_B"

#include "../../../src/comb/ball_box/ddm/lib.hpp"
#include "../../../src/comb/binom/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/fact/helper/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;
using namespace tifa_libs;
using fact_t = math::fact_helper<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::math::binom<mint, fact_t> binom(2001);
  std::cout << tifa_libs::math::ball_box_ddm<mint>(n, k, binom) << '\n';
  return 0;
}
