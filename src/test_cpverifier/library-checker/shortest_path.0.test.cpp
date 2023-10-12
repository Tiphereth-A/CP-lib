#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../../code/graph/dijkstra.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, m, s, t;
  std::cin >> n >> m >> s >> t;
  tifa_libs::vvec<std::pair<size_t, tifa_libs::u64>> g(n);
  for (tifa_libs::u32 i = 0, a, b, c; i < m; ++i) {
    std::cin >> a >> b >> c;
    g[a].emplace_back(b, c);
  }
  tifa_libs::vec<tifa_libs::i32> pre(n, -1);
  auto dis = tifa_libs::graph::dijkstra(g, s, [&pre](size_t now, size_t to) { pre[to] = (tifa_libs::i32)now; });
  tifa_libs::vec<tifa_libs::i32> ans;
  for (tifa_libs::i32 now = pre[t]; ~now; now = pre[(size_t)now]) ans.push_back(now);
  if (ans.empty()) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << dis[t] << ' ' << ans.size() << '\n';
  for (size_t i = ans.size() - 1; i; --i) std::cout << ans[i] << ' ' << ans[i - 1] << '\n';
  std::cout << ans[0] << ' ' << t << '\n';
  return 0;
}
