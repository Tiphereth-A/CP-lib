#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_B"

#include "../../code/ds/segtree.hpp"

u32 op(u32 x, u32 y) { return x + y; }
void mapping(u32& x, u32 y) { x += y; }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::segtree_notag<u32, op, mapping> tr(0, n);
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u - 1, v) << '\n';
    else tr.update(u - 1, v);
  }
  return 0;
}
