#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"

#include "../../code/comb/ball_box_idm.hpp"
#include "../../code/comb/binom.hpp"
#include "../../code/math/mint_s30.hpp"

constexpr u32 MOD = 1000000000 + 7;
using mint = tifa_libs::math::mint_s30<MOD>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n, k;
  std::cin >> n >> k;
  tifa_libs::math::Binom binom(MOD, 2001);
  std::cout << tifa_libs::math::ball_box_idm<mint>(n, k, binom) << '\n';
  return 0;
}
