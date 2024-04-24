#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_5_B"

#include "../../code/ds/fenwick_2d.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::ds::fenwick2d<u32> tr(1003, 1003);
  u32 n;
  std::cin >> n;
  for (u32 i = 0, xl, xr, yl, yr; i < n; ++i) {
    std::cin >> xl >> yl >> xr >> yr;
    tr.add(xl + 1, yl + 1, xr + 1, yr + 1, 1);
  }
  u32 mx = 0;
  for (u32 i = 1; i <= 1001; ++i)
    for (u32 j = 1; j <= 1001; ++j) mx = std::max(mx, tr.sum(i, j));
  std::cout << mx << '\n';
  return 0;
}
