#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_B"

#include "../../code/ds/segtree.hpp"

u32 op(u32 x, u32 y) { return x + y; }
u32 e() { return 0; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::segtree_notag<u32, op, e> tr(n);
  for (u32 i = 0; i < q; ++i) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u - 1, v - 1) << '\n';
    else tr.update(u - 1, v);
  }
  return 0;
}
