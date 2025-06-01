#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_B"

#include "../../include/ds/dsu_weighted.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  ds::dsu_weighted dsu(n);
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) {
      if (!dsu.same(u, v)) std::cout << "?\n";
      else std::cout << dsu.diff(u, v) << '\n';
    } else {
      i64 k;
      std::cin >> k;
      dsu.merge(u, v, k);
    }
  }
  return 0;
}
