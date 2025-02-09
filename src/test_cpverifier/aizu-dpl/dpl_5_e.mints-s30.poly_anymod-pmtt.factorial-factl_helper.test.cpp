#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"

#include "../../code/comb/ball_box_idm.hpp"
#include "../../code/comb/binom.hpp"

CEXP u32 MOD = 1000000000 + 7;

#include "../../code/math/factl_helper.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using poly = tifa_libs::math::polymtt<mint>;
using fact_t = tifa_libs::math::factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::math::binom<mint, fact_t> binom(2001);
  std::cout << tifa_libs::math::ball_box_idm<mint>(n, k, binom) << '\n';
  return 0;
}
