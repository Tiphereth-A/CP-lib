#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_L"

#include "../../code/comb/ball_box_iil.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d31.hpp"
#include "../../code/poly/polydata_d.hpp"

constexpr u32 MOD = 1000000000 + 7;
using mintdata = tifa_libs::math::mintdata_d31<-1>;
using mint = tifa_libs::math::mint<mintdata>;
using pdata = tifa_libs::math::polydata_d<mint>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::math::ball_box_iil<pdata>(n, k) << '\n';
  return 0;
}
