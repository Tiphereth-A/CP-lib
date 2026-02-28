#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_L"

#include "../../../src/comb/ball_box/iil/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_bs, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_bs, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_bs, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_iil<poly>(n, k) << '\n';
  return 0;
}
