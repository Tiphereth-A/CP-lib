#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_L"

#include "../../code/comb/ball_box_iil.hpp"
#include "../../code/math/mint_d63.hpp"
#include "../../code/poly/polymtt.hpp"

constexpr u32 MOD = 1000000000 + 7;
using mint = tifa_libs::math::mint_d63<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_iil<poly>(n, k) << '\n';
  return 0;
}
