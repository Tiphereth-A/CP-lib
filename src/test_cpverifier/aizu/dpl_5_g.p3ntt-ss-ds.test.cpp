#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_G"

#include "../../code/comb/ball_box_dia.hpp"
#include "../../code/comb/gen_bell.hpp"

constexpr u32 MOD = 1000000000 + 7;

#include "../../code/math/mint_ds.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using mint1 = tifa_libs::math::mint_ss<167772161>;
using mint2 = tifa_libs::math::mint_ss<469762049>;
using mint3 = tifa_libs::math::mint_ss<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

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
