#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../../code/graph/adjlist.hpp"
#include "../../code/graph/dijkstra.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, s, t;
  std::cin >> n >> m >> s >> t;
  tifa_libs::graph::adjlist<u64> g(n);
  for (u32 i = 0, a, b, c; i < m; ++i) {
    std::cin >> a >> b >> c;
    g.add_arc(a, b, c);
  }
  vec<i32> pre(n, -1);
  auto dis = tifa_libs::graph::dijkstra(g, s, [&pre](usz now, usz to) { pre[to] = (i32)now; });
  vec<i32> ans;
  for (i32 now = pre[t]; ~now; now = pre[(usz)now]) ans.push_back(now);
  if (ans.empty()) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << dis[t] << ' ' << ans.size() << '\n';
  for (usz i = ans.size() - 1; i; --i) std::cout << ans[i] << ' ' << ans[i - 1] << '\n';
  std::cout << ans[0] << ' ' << t << '\n';
  return 0;
}
