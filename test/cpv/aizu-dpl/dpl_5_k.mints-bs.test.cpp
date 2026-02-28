#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_K"

#include "../../../src/comb/ball_box/iim/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_iim<mint>(n, k) << '\n';
  return 0;
}
