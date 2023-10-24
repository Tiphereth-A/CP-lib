#define PROBLEM "https://codeforces.com/gym/103446/problem/H"

#include "../../code/graph/kruskal_reconstruction_tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, q;
  std::cin >> n >> m >> q;
  vec<u32> nw(n);
  for (auto& x : nw) std::cin >> x;
  vec<std::tuple<u32, u32, u32>> e(m);
  for (auto& [w, u, v] : e) std::cin >> u >> v >> w, --u, --v;
  auto [tr, ew] = tifa_libs::graph::kruskal_re_tree(e, n, nw);
  n = tr.v_size();
  tr.reset_dfs_info<tifa_libs::graph::s_go | tifa_libs::graph::s_sum_node_w>();
  while (q--) {
    u32 x, k;
    std::cin >> x >> k;
    --x;
    u64 ans = k + tr.sum_node_w[x];
    while (x != tr.rt) {
      u32 tem = x;
      for (i32 i = 20; i >= 0; i--) {
        if (tr.go[x][i] < n && ew[tr.go[x][i]] <= ans) x = tr.go[x][i];
      }
      if (x == tem) break;
      ans = k + tr.sum_node_w[x];
    }
    std::cout << ans << '\n';
  }
  return 0;
}
