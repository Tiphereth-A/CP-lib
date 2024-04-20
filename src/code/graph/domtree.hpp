#ifndef TIFALIBS_GRAPH_DOMTREE
#define TIFALIBS_GRAPH_DOMTREE

#include "alist.hpp"

namespace tifa_libs::graph {

class domtree {
  u32 n, t;
  alist<> const& g;
  alist<> rg;
  vvecu bucket;
  vecu arr, par, rev, dsu, label;

  void dfs(u32 u) {
    rev[arr[u] = label[t] = sdom[t] = dsu[t] = t] = u;
    ++t;
    for (u32 w : g.g[u]) {
      if (!~arr[w]) {
        dfs(w);
        par[arr[w]] = arr[u];
      }
      rg.add_arc(arr[w], arr[u]);
    }
  }
  u32 find(u32 u, int x = 0) {
    if (u == dsu[u]) return x ? -1_u32 : u;
    u32 v = find(dsu[u], x + 1);
    if (!~v) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
  }

 public:
  vecu sdom, dom;

  domtree(alist<> const& g) : n((u32)g.g.size()), t(0), g(g), rg(n), bucket(n), arr(n, -1_u32), par(n, -1_u32), rev(n, -1_u32), dsu(n), label(n), sdom(n, -1_u32), dom(n, -1_u32) {}

  // @return p, parents of dominator tree, p_i = -1_u32 if not exist else parent of vertex i
  vecu get_domtree(u32 root) {
    dfs(root);
    std::iota(dom.begin(), dom.end(), 0);
    for (u32 i = t - 1; ~i; --i) {
      for (u32 w : rg.g[i]) sdom[i] = std::min(sdom[i], sdom[find(w)]);
      if (i) bucket[sdom[i]].push_back(i);
      for (u32 w : bucket[i])
        if (u32 v = find(w); sdom[v] == sdom[w]) dom[w] = sdom[w];
        else dom[w] = v;
      if (i > 1) dsu[i] = par[i];
    }
    for (u32 i = 1; i < t; ++i)
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    vecu fa(n, -1_u32);
    for (u32 i = 1; i < t; ++i) fa[rev[i]] = rev[dom[i]];
    fa[root] = root;
    return fa;
  }
};

}  // namespace tifa_libs::graph

#endif