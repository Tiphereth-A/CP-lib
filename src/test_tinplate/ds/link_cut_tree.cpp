#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum/"

#include "../../code/ds/link_cut_tree.hpp"

auto op(u64 a, u64 b) { return a + b; }
auto inv_op(u64 a, u64 b) { return a - b; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u64> a(n);
  for (auto &x : a) x = 1;
  tifa_libs::ds::link_cut_tree<u64, op, inv_op> lct(n, a);
  for (u32 i = 0; i < m; ++i) {
    char opt; 
    u32 u, v;
    std::cin >> opt >> u >> v;
    --u, --v;
    if (opt == 'A') lct.link(u, v);
    else {
        auto ret = lct.query_subtree(u, v);
        std::cout << ret.first * ret.second << '\n';
    }
  }
  return 0;
}
