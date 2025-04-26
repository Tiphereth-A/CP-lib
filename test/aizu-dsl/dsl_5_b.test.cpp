#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_5_B"

#include "../../include/ds/fenwick_2d.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  tifa_libs::ds::fenwick2d<u32> tr(1003, 1003);
  u32 n;
  std::cin >> n;
  for (u32 i = 0, xl, xr, yl, yr; i < n; ++i) {
    std::cin >> xl >> yl >> xr >> yr;
    tr.add(xl + 1, yl + 1, xr + 1, yr + 1, 1);
  }
  u32 mx = 0;
  flt_ (u32, i, 1, 1002)
    flt_ (u32, j, 1, 1002) mx = std::max(mx, tr.sum(i, j));
  std::cout << mx << '\n';
  return 0;
}
