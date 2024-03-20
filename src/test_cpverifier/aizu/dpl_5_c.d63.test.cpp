#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_C"

#include "../../code/comb/ball_box_ddl.hpp"
#include "../../code/comb/binom.hpp"
#include "../../code/math/mint_d63.hpp"

constexpr u32 MOD = 1000000000 + 7;
using mint = tifa_libs::math::mint_d63<-1>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::math::Binom<mint> binom(2001);
  std::cout << tifa_libs::math::ball_box_ddl<mint>(n, k, binom) << '\n';
  return 0;
}
