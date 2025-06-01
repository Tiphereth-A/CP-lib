#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_H"

#include "../../include/comb/ball_box_dim.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_dim<mint>(n, k) << '\n';
  return 0;
}
