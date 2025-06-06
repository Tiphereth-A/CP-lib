#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H"

#include "../../include/ds/segtree_ctor.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  auto tr = ds::segtl_addmin_ctor<i32>(INT32_MAX, veci(n));
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    i32 w;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u, v + 1) << '\n';
    else (std::cin >> w), tr.update(u, v + 1, w);
  }
  return 0;
}
