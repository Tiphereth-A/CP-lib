#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_E"

#include "../../code/ds/segtree.hpp"

u32 op(u32 x, u32 y) { return x + y; }
u32 e() { return 0; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::segtree<u32, op, e, u32, op, op, e> tr(n);
  for (u32 i = 0; i < q; ++i) {
    u32 op, u, v, w;
    std::cin >> op >> u;
    if (op) std::cout << tr.query(u - 1) << '\n';
    else (std::cin >> v >> w), tr.update(u - 1, v - 1, w);
  }
  return 0;
}
