#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../../include/graph/alist.hpp"
#include "../../include/graph/dijkstra.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

using namespace tifa_libs;
int main() {
  u32 n, m, s, t;
  fin_uint >> n >> m >> s >> t;
  graph::alistw<u64> g(n);
  for (u32 i = 0, a, b, c; i < m; ++i) {
    fin_uint >> a >> b >> c;
    g.add_arc(a, b, c);
  }
  veci pre(n, -1);
  auto dis = graph::dijkstra(g, s, [&pre](u32 now, u32 to) { pre[to] = (i32)now; });
  veci ans;
  for (i32 now = pre[t]; ~now; now = pre[(usz)now]) ans.push_back(now);
  if (ans.empty()) {
    fout << "-1\n";
    return 0;
  }
  fout << dis[t] << ' ' << ans.size() << '\n';
  for (u32 i = u32(ans.size() - 1); i; --i) fout << ans[i] << ' ' << ans[i - 1] << '\n';
  fout << ans[0] << ' ' << t << '\n';
  return 0;
}
