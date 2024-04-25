#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_I"

#include "../../code/ds/segtree_ctor.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  auto tr = tifa_libs::ds::segtl_setsum_ctor<i64, -INT32_MAX>(vec<i64>(n));
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    i64 w;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u, v + 1) << '\n';
    else (std::cin >> w), tr.update(u, v + 1, w);
  }
  return 0;
}
