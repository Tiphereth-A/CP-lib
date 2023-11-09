#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_A"

#include "../../code/ds/dsu_basic.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_basic dsu(n);
  for (usz i = 0; i < q; ++i) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op)
      std::cout << dsu.same(u, v) << '\n';
    else
      dsu.merge(u, v);
  }
  return 0;
}
