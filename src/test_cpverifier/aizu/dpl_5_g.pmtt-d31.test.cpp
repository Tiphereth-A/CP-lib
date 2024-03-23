#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_G"

#include "../../code/comb/ball_box_dia.hpp"
#include "../../code/comb/gen_bell.hpp"

constexpr u32 MOD = 1000000000 + 7;

#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  if (k >= n) std::cout << tifa_libs::math::gen_bell<poly>(n)[n] << '\n';  // unnecessary, just for test
  else std::cout << tifa_libs::math::ball_box_dia<poly>(n, k) << '\n';
  return 0;
}
