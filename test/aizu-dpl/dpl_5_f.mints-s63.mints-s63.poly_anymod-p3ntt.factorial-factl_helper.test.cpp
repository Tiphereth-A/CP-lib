#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_F"

#include "../../include/comb/ball_box_idl.hpp"
#include "../../include/comb/binom.hpp"

CEXP u32 MOD = 1000000000 + 7;

#include "../../include/math/factl_helper.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using mint_p3ntt1 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 167772161>;
using mint_p3ntt2 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 469762049>;
using mint_p3ntt3 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;
using fact_t = tifa_libs::math::factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::math::binom<mint, fact_t> binom(2001);
  std::cout << tifa_libs::math::ball_box_idl<mint>(n, k, binom) << '\n';
  return 0;
}
