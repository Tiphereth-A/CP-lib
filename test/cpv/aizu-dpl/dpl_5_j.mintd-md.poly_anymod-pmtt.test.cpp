#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_J"

#include "../../../src/comb/ball_box/iia/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_iia<poly>(n, k) << '\n';
  return 0;
}
