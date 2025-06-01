#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_D"

#include "../../include/ds/segtree_ctor.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  auto tr = ds::segtl_setsum_ctor<i64>(INT64_MAX, vecii(n, 2147483647));
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    i64 w;
    std::cin >> op >> u;
    if (op) std::cout << tr.query(u) << '\n';
    else (std::cin >> v >> w), tr.update(u, v + 1, w);
  }
  return 0;
}
