#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include "../../include/ds/segtree.hpp"

u32 op(u32 x, u32 y) { return std::min(x, y); }
void mapping(u32& x, u32 y) { x = op(x, y); }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::segtree_notag<u32, op, mapping> tr(2147483647, n);
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u, v + 1) << '\n';
    else tr.set(u, v);
  }
  return 0;
}
