#ifndef TIFALIBS_GRAPH_EULER_TRAIL
#define TIFALIBS_GRAPH_EULER_TRAIL

#include "../util/traits.hpp"

namespace tifa_libs::graph {
namespace euler_trail_impl_ {
template <bool cyc>
CEXP std::optional<vecptu> run_(u32 n, u32 m, cT_(vvecptu) g, u32 s) NE {
  vec<vecptu::const_iterator> its(n);
  flt_ (u32, i, 0, n) its[i] = g[i].begin();
  veci f(n);
  if CEXP (!cyc) ++f[s];
  vecb vis(m);
  vecptu ret, stk = {{s, -1_u32}};
  while (!stk.empty()) {
    auto [i, p] = stk.back();
    auto &it = its[i];
    if (it == g[i].end()) {
      ret.emplace_back(i, p), stk.pop_back();
      continue;
    }
    if (auto [j, e] = *(it++); !vis[e]) --f[i], ++f[j], stk.emplace_back(j, e), vis[e] = true;
  }
  if (ret.size() != m + 1) return {};
  for (i32 i : f)
    if (i < 0) return {};
  reverse(ret);
  return ret;
}
}  // namespace euler_trail_impl_

// @return vector of {v, eid} of Eulerian trail if found
// edges[eid[i]] = v[i-1] -> v[i], eid[0] = -1
template <bool directed, bool cycle = false>
CEXP std::optional<vecptu> euler_trail(u32 n, vecptu CR edges) NE {
  vvecptu g(n);
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
CEXP bool is_eulerian(alist_c auto CR g) NE {
  const u32 n = g.size();
  assert(n == g.deg_in.size());
  vecb vis(n);
  u32 cnt = 0;
  auto f = [&](auto &&f, u32 x) NE -> void {
    for (auto v : g[x])
      if (++cnt; !vis[(u32)v]) vis[(u32)v] = 1, f(f, (u32)v);
  };
  if (vis[0] = 1, f(f, 0); g.cnt_arc != cnt) return 0;
  flt_ (u32, i, 0, n)
    if (g.deg_in[i] != g.deg_out[i]) return 0;
  return 1;
}

}  // namespace tifa_libs::graph

#endif