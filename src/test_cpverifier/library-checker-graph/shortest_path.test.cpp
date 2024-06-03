#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../../code/graph/dijkstra.hpp"
#include "../../code/io/fastio.hpp"

int main() {
  u32 n, m, s, t;
  tifa_libs::fin >> n >> m >> s >> t;
  tifa_libs::graph::alistw<u64> g(n);
  for (u32 i = 0, a, b, c; i < m; ++i) {
    tifa_libs::fin >> a >> b >> c;
    g.add_arc(a, b, c);
  }
  veci pre(n, -1);
  auto dis = tifa_libs::graph::dijkstra(g, s, [&pre](u32 now, u32 to) { pre[to] = (i32)now; });
  veci ans;
  for (i32 now = pre[t]; ~now; now = pre[(usz)now]) ans.push_back(now);
  if (ans.empty()) {
    tifa_libs::fout << "-1\n";
    return 0;
  }
  tifa_libs::fout << dis[t] << ' ' << ans.size() << '\n';
  for (u32 i = u32(ans.size() - 1); i; --i) tifa_libs::fout << ans[i] << ' ' << ans[i - 1] << '\n';
  tifa_libs::fout << ans[0] << ' ' << t << '\n';
  return 0;
}
