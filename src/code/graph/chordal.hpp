#ifndef TIFALIBS_GRAPH_CHORDAL
#define TIFALIBS_GRAPH_CHORDAL

#include "alist.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
class chordal {
  alist<with_deg> const& g;

 public:
  vecu peo, rnk;

  // @param g simple UNDIRECTED graph
  //! g.g[i] MUST be sorted
  explicit constexpr chordal(alist<with_deg> const& g) : g(g), peo(g.g.size()), rnk(peo.size()) {
    for (auto& i : g.g) assert(std::ranges::is_sorted(i));
    u32 n = (u32)peo.size();
    vecu l(n * 2 + 1), r, idx(n);
    std::iota(l.begin(), l.end(), 0);
    r = l;
    auto ins = [&](u32 i, u32 j) { r[l[i] = l[j]] = i, r[l[j] = i] = j; };
    auto del = [&](u32 i) { r[l[i]] = r[i], l[r[i]] = l[i]; };
    for (u32 i = 0; i < n; ++i) ins(i, n);
    u32 li = n;
    for (u32 i = 0; i < n; ++i) {
      ++li;
      while (l[li] == li) --li;
      u32 v = l[li];
      idx[v] = -1_u32, del(v);
      for (u32 to : g.g[v])
        if (~idx[to]) del(to), ins(to, n + (++idx[to]));
      peo[i] = v;
    }
    std::ranges::reverse(peo);
    for (u32 i = 0; i < n; ++i) rnk[peo[i]] = i;
  }

  template <bool find_indcycle = false>
  std::conditional_t<find_indcycle, std::optional<vecu>, bool> is_chordal_graph() const {
    for (u32 u : peo) {
      vecu s;
      s.reserve(g.g[u].size());
      for (auto v : g.g[u])
        if (rnk[u] < rnk[v]) {
          s.push_back(v);
          if (rnk[s.back()] < rnk[s[0]]) std::swap(s[0], s.back());
        }
      for (u32 j = 1; j < s.size(); ++j)
        if (!std::ranges::binary_search(g.g[s[0]], s[j])) {
          if constexpr (!find_indcycle) return false;
          else {
            u32 x = s[j], y = s[0], z = u;
            vecu pre(peo.size(), -1_u32);
            std::queue<u32> q({x});
            while (!q.empty()) {
              u32 t = q.front();
              q.pop();
              if (std::ranges::binary_search(g.g[t], y)) {
                pre[y] = t;
                vecu path = {y};
                while (path.back() != x) path.push_back(pre[path.back()]);
                path.push_back(z);
                return path;
              }
              for (u32 u : g.g[t])
                if (u != z && !std::ranges::binary_search(g.g[u], z) && !~pre[u]) pre[u] = t, q.push(u);
            }
          }
        }
    }
    if constexpr (find_indcycle) return {};
    else return true;
  }
  // @return {x}, which $\{x\}+N(x)$ be a maximal clique
  constexpr vecu maximal_cliques() const {
    vecu fst(peo.size(), -1_u32), n(peo.size()), res;
    vecb vis(peo.size());
    for (u32 u : peo)
      for (auto v : g.g[u])
        if (rnk[u] < rnk[v]) {
          ++n[u];
          if (!~fst[u] || rnk[v] < rnk[fst[u]]) fst[u] = v;
        }
    for (u32 u : peo) {
      if (vis[u]) continue;
      res.push_back(u);
      vis[fst[u]] = n[u] > n[fst[u]];
    }
    return res;
  }
  constexpr u32 chromatic_number() const {
    u32 ans = 0;
    for (auto& i : g) ans = std::max(ans, (u32)i.size());
    return ans + 1;
  }
  constexpr vecu max_independent_set() const {
    vecu res;
    vecb vis(peo.size());
    for (u32 u : peo) {
      if (vis[u]) continue;
      res.push_back(u);
      for (u32 v : g.g[u]) vis[v] = true;
    }
    return res;
  }
};

}  // namespace tifa_libs::graph

#endif