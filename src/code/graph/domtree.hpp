#ifndef TIFALIBS_GRAPH_DOMTREE
#define TIFALIBS_GRAPH_DOMTREE

#include "../util/traits.hpp"

namespace tifa_libs::graph {

template <class G>
requires(adjlist_c<G> && !adjlistw_c<G>)
class domtree {
  u32 n, t;
  G CR g;
  G rg;
  vvecu bucket;
  vecu arr, par, rev, dsu, label;

  CEXP void dfs(u32 u) {
    for (rev[arr[u] = label[t] = sdom[t] = dsu[t] = t] = u, ++t; u32 w : g[u]) {
      if (!~arr[w]) dfs(w), par[arr[w]] = arr[u];
      rg.add_arc(arr[w], arr[u]);
    }
  }
  CEXP u32 find(u32 u, int x = 0) {
    if (u == dsu[u]) return x ? -1_u32 : u;
    const u32 v = find(dsu[u], x + 1);
    if (!~v) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    return dsu[u] = v, x ? v : label[u];
  }

 public:
  vecu sdom, dom;

  CEXPE domtree(G CR g) : n((u32)g.size()), t(0), g(g), rg(n), bucket(n), arr(n, -1_u32), par(n, -1_u32), rev(n, -1_u32), dsu(n), label(n), sdom(n, -1_u32), dom(n, -1_u32) {}

  // @return p, parents of dominator tree, p_i = -1_u32 if not exist else parent of vertex i
  CEXP vecu get_domtree(u32 root) {
    dfs(root), rg.build(), std::iota(dom.begin(), dom.end(), 0);
    for (u32 i = t - 1; ~i; --i) {
      for (auto w : rg[i]) sdom[i] = min(sdom[i], sdom[find((u32)w)]);
      if (i) bucket[sdom[i]].push_back(i);
      for (u32 w : bucket[i])
        if (u32 v = find(w); sdom[v] == sdom[w]) dom[w] = sdom[w];
        else dom[w] = v;
      if (i > 1) dsu[i] = par[i];
    }
    flt_ (u32, i, 1, t)
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    vecu fa(n, -1_u32);
    flt_ (u32, i, 1, t) fa[rev[i]] = rev[dom[i]];
    return fa[root] = root, fa;
  }
};

}  // namespace tifa_libs::graph

#endif