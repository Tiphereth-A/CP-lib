#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_F"

#include "../../code/comb/ball_box_idl.hpp"
#include "../../code/comb/binom.hpp"

CEXP u32 MOD = 1000000000 + 7;

#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::math::Binom<mint> binom(2001);
  std::cout << tifa_libs::math::ball_box_idl<mint>(n, k, binom) << '\n';
  return 0;
}
