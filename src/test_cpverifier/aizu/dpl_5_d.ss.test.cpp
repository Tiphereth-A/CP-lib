#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_D"

#include "../../code/comb/ball_box_ida.hpp"
#include "../../code/comb/binom.hpp"

constexpr u32 MOD = 1000000000 + 7;

#include "../../code/math/mint_ss.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::math::Binom<mint> binom(2001);
  std::cout << tifa_libs::math::ball_box_ida<mint>(n, k, binom) << '\n';
  return 0;
}
