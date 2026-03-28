#pragma once

#include "../../util/alias/others/lib.hpp"
#include "../ds/graph_c/lib.hpp"

namespace tifa_libs {

template <graph_c G>  // prefer alist
class chordal {
  G CR g;
  vecu deg;

 public:
  vecu peo, rnk;

  // @param g simple UNDIRECTED graph
  //! g[i] MUST be sorted
  CEXPE chordal(G CR g) NE : g(g), deg(g.vsize()), peo(g.vsize()), rnk(g.vsize()) {
    const u32 n = g.vsize();
    vecu l(n * 2 + 1), r, idx(n);
    std::iota(begin(l), end(l), 0), r = l;
    auto ins = [&](u32 i, u32 j) NE { r[l[i] = l[j]] = i, r[l[j] = i] = j; };
    auto del = [&](u32 i) NE { r[l[i]] = r[i], l[r[i]] = l[i]; };
    flt_ (u32, i, 0, n) ins(i, n);
    u32 li = n;
    flt_ (u32, i, 0, n) {
      ++li;
      while (l[li] == li) --li;
      u32 v = l[li];
      for (idx[v] = -1_u32, del(v); u32 to : g[v])
        if (~idx[to]) ++deg[to], del(to), ins(to, n + (++idx[to]));
      peo[i] = v;
    }
    reverse(peo);
    flt_ (u32, i, 0, n) rnk[peo[i]] = i;
  }

  template <bool find_indcycle = false>
  std::conditional_t<find_indcycle, std::optional<vecu>, bool> is_chordal_graph() CNE {
    std::optional<vecu> ret;
    auto has_edge = [&](u32 u, u32 v) { return binary_search(g[u], v, {}, [](auto CR e) { return (u32)e; }); };
    for (u32 u : peo) {
      vecu s;
      for (s.reserve(g.deg_out(u)); auto v : g[u])
        if (rnk[u] < rnk[v])
          if (s.push_back(v); rnk[s.back()] < rnk[s[0]]) swap(s[0], s.back());
      flt_ (u32, j, 1, (u32)s.size())
        if (!has_edge(s[0], s[j])) {
          if CEXP (!find_indcycle) return false;
          else {
            u32 x = s[j], y = s[0], z = u;
            vecu pre(peo.size(), -1_u32);
            std::queue<u32> q({x});
            while (!q.empty()) {
              u32 t = q.front();
              if (q.pop(); has_edge(t, y)) {
                pre[y] = t;
                ret.emplace({y});
                while (ret->back() != x) ret->push_back(pre[ret->back()]);
                ret->push_back(z);
                return ret;
              }
              for (u32 u : g[t])
                if (u != z && !has_edge(u, z) && !~pre[u]) pre[u] = t, q.push(u);
            }
          }
        }
    }
    if CEXP (find_indcycle) return ret;
    else return true;
  }
  // @return {x}, which $\{x\}+N(x)$ be a maximal clique
  CEXP vecu maximal_cliques() CNE {
    vecu fst(peo.size(), -1_u32), n(peo.size()), res;
    for (u32 u : peo)
      for (auto v : g[u])
        if (rnk[u] < rnk[(u32)v])
          if (++n[u]; !~fst[u] || rnk[(u32)v] < rnk[fst[u]]) fst[u] = (u32)v;
    for (vecb vis(peo.size()); u32 u : peo) {
      if (vis[u]) continue;
      res.push_back(u), vis[fst[u]] = n[u] > n[fst[u]];
    }
    return res;
  }
  CEXP u32 chromatic_number() CNE { return max(deg) + 1; }
  CEXP vecu max_independent_set() CNE {
    vecu res;
    for (vecb vis(peo.size()); u32 u : peo) {
      if (vis[u]) continue;
      for (res.push_back(u); u32 v : g[u]) vis[v] = true;
    }
    return res;
  }
};

}  // namespace tifa_libs
