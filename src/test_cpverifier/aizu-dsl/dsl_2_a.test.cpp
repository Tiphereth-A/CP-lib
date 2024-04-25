#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include "../../code/ds/segtree.hpp"

u32 op(u32 x, u32 y) { return tifa_libs::min(x, y); }
u32 e() { return 2147483647; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::segtree_notag<u32, op, e> tr(n);
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u, v + 1) << '\n';
    else tr.set(u, v);
  }
  return 0;
}
