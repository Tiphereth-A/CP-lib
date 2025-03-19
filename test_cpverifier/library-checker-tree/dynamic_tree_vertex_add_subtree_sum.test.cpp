#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum/"

#include "../../include/ds/link_cut_tree.hpp"

auto op(u64 a, u64 b) { return a + b; }
auto inv_op(u64 a, u64 b) { return a - b; }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vecuu a(n);
  for (auto &x : a) std::cin >> x;
  tifa_libs::ds::link_cut_tree<u64, op, inv_op> lct(n, a);
  for (u32 i = 1, u, v; i < n; ++i) std::cin >> u >> v, lct.link(u, v);
  flt_ (u32, i, 0, m) {
    u32 opt, u, v;
    std::cin >> opt >> u >> v;
    if (opt == 0) {
      u32 p, q;
      std::cin >> p >> q;
      lct.cut(u, v), lct.link(p, q);
    } else if (opt == 1) lct.node_add(u, v);
    else std::cout << lct.query_subtree(u, v).first << '\n';
  }
  return 0;
}
