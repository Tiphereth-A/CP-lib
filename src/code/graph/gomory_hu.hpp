#ifndef TIFALIBS_GRAPH_GOMORY_HU
#define TIFALIBS_GRAPH_GOMORY_HU

#include "dinic.hpp"

namespace tifa_libs::graph {

// @return {w, u, v} edges in Gomory--Hu tree
template <class EW>
CEXP vec<edge_t<EW>> gomory_hu(u32 n, vec<edge_t<EW>> CR ed) {
  vecu par(n);
  dinic<EW> D(n);
  vecptu ed_locs;
  for (auto [w, u, v] : ed) ed_locs.push_back(D.add(u, v, w, w));
  vec<edge_t<EW>> ans;
  flt_ (u32, i, 1, n) {
    for (auto [ed, loc] : ed_locs) {
      auto &e = D.e[ed][loc], &e_rev = D.e[e.to][e.inv];
      e.w = e_rev.w = (e.w + e_rev.w) / 2;
    }
    ans.emplace_back(D.template get<EW>(i, par[i]), i, par[i]);
    flt_ (u32, j, i + 1, n)
      if (par[j] == par[i] && D.dep[j]) par[j] = i;
  }
  return ans;
}

}  // namespace tifa_libs::graph

#endif