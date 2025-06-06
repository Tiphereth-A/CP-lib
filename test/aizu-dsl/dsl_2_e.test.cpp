#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_E"

#include "../../include/ds/segtree_ctor.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  auto tr = ds::segtl_addsum_ctor(vecuu(n));
  flt_ (u32, i, 0, q) {
    u32 op, u, v, w;
    std::cin >> op >> u;
    if (op) std::cout << tr.query(u - 1) << '\n';
    else (std::cin >> v >> w), tr.update(u - 1, v, w);
  }
  return 0;
}
