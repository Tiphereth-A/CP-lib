#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_L"

#include "../../include/comb/ball_box_iil.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/poly/poly3ntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_s30, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_s30, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_s30, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_iil<poly>(n, k) << '\n';
  return 0;
}
