#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G"

#include "../../code/ds/segtree_ctor.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  auto tr = tifa_libs::ds::segtl_addsum_ctor(vec<u64>(n));
  flt_ (u32, i, 0, q) {
    u32 op, u, v, w;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u - 1, v) << '\n';
    else (std::cin >> w), tr.update(u - 1, v, w);
  }
  return 0;
}
