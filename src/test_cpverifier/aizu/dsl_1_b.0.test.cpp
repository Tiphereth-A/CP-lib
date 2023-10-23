#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_B"

#include "../../code/ds/dsu_weighted.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_weighted dsu(n);
  for (size_t i = 0; i < q; ++i) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) {
      if (!dsu.same(u, v))
        std::cout << "?\n";
      else
        std::cout << dsu.depth(u) - dsu.depth(v) << '\n';
    } else {
      i64 k;
      std::cin >> k;
      dsu.merge(u, v, k);
    }
  }
  return 0;
}
