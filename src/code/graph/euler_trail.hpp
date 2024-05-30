#ifndef TIFALIBS_GRAPH_EULER_TRAIL
#define TIFALIBS_GRAPH_EULER_TRAIL

#include "../util/util.hpp"

namespace tifa_libs::graph {
namespace euler_trail_impl_ {
template <bool cyc>
CEXP std::optional<vecpt<u32>> run_(u32 n, u32 m, cT_(vvecpt<u32>) g, u32 s) {
  vec<vecpt<u32>::const_iterator> its(n);
  flt_ (u32, i, 0, n) its[i] = g[i].begin();
  vec<i32> f(n);
  if CEXP (!cyc) ++f[s];
  vecb vis(m);
  vecpt<u32> ret, stk = {{s, -1_u32}};
  while (!stk.empty()) {
    auto [i, p] = stk.back();
    auto &it = its[i];
    if (it == g[i].end()) {
      ret.emplace_back(i, p), stk.pop_back();
      continue;
    }
    auto [j, e] = *(it++);
    if (!vis[e]) --f[i], ++f[j], stk.emplace_back(j, e), vis[e] = true;
  }
  if (ret.size() != m + 1) return {};
  for (i32 i : f)
    if (i < 0) return {};
  std::ranges::reverse(ret);
  return ret;
}
}  // namespace euler_trail_impl_

// @return vector of {v, eid} of Euler trail if found
// edges[eid[i]] = v[i-1] -> v[i], eid[0] = -1
template <bool directed, bool cycle = false>
CEXP std::optional<vecpt<u32>> euler_trail(u32 n, cT_(vecpt<u32>) edges) {
  vvecpt<u32> g(n);
  vecu deg_in(0);
  if CEXP (directed) deg_in.resize(n);
  u32 e = 0;
  for (auto [u, v] : edges) {
    g[u].emplace_back(v, e);
    if CEXP (directed) ++deg_in[v];
    else g[v].emplace_back(u, e);
    ++e;
  }
  u32 s = 0;
  flt_ (u32, i, 1, (u32)g.size())
    if (!g[i].empty()) s = i;
  flt_ (u32, i, 0, (u32)g.size())
    if CEXP (directed) {
      if (deg_in[i] < g[i].size()) s = i;
    } else if (g[i].size() & 1) s = i;
  return euler_trail_impl_::run_<cycle>(n, (u32)edges.size(), g, s);
}

}  // namespace tifa_libs::graph

#endif