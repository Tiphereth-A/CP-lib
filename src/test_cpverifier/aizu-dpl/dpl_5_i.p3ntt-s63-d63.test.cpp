#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_I"

#include "../../code/comb/ball_box_dil.hpp"

CEXP u32 MOD = 1000000000 + 7;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d63.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using mint1 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 167772161>;
using mint2 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 469762049>;
using mint3 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_dil<poly>(n, k) << '\n';
  return 0;
}
