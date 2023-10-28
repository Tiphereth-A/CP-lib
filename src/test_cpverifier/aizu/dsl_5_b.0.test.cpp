#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_5_B"

#include "../../code/ds/fenwick_2d.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n;
  std::cin >> n;
  tifa_libs::ds::fenwick2d<u32> fw(1001, 1001);
  for (u32 i = 0, xl, xr, yl, yr; i < n; ++i) {
    std::cin >> xl >> yl >> xr >> yr;
    fw.add(xl, yl, xr, yr, 1);
  }
  u32 mx = 0;
  for (u32 i = 0; i <= 1000; ++i)
    for (u32 j = 0; j <= 1000; ++j) mx = std::max(mx, fw.sum(i, j));
  std::cout << mx << '\n';
  return 0;
}
