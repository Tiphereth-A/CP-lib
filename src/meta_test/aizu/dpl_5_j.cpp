#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_J"

#include "../../code/comb/ball_box_iia.hpp"

constexpr u32 MOD = 1000000000 + 7;

#define GENTCs_pmttd0
#define GENTCs_p3nttd0

int main() {
#define GENTCs_pmttd1
#define GENTCs_p3nttd1
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_iia<poly>(n, k) << '\n';
  return 0;
}
