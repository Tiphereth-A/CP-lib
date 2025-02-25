#ifndef TIFALIBS_GRAPH_RINGCNT4
#define TIFALIBS_GRAPH_RINGCNT4

#include "../util/traits.hpp"

namespace tifa_libs::graph {
namespace ringcnt4_impl_ {
template <class G>
requires(alist_c<G> && !alistw_c<G>)
CEXP u64 run(G CR dg, G CR dgv) NE {
  const u32 n = dg.size();
  u64 ans = 0;
  vecuu cnt1(n), cnt2(n);
  flt_ (u32, u, 0, n) {
    for (auto v : dg[u])
      for (auto w : dg[(u32)v]) ++cnt1[(u32)w];
    for (auto v : dgv[u])
      for (auto w : dg[(u32)v])
        if ((u32)w != u) ++cnt2[(u32)w];
    for (auto v : dg[u])
      for (auto w : dg[(u32)v]) {
        ans += cnt1[(u32)w] * (cnt1[(u32)w] - 1) + cnt1[(u32)w] * cnt2[(u32)w] * 2;
        cnt1[(u32)w] = 0;
      }
    for (auto v : dgv[u])
      for (auto w : dg[(u32)v])
        if ((u32)w != u) ans += cnt2[(u32)w] * (cnt2[(u32)w] - 1) / 2, cnt2[(u32)w] = 0;
  }
  return ans / 2;
}
}  // namespace ringcnt4_impl_

//! should be simple undirected graph
template <class G>
requires(alist_c<G> && !alistw_c<G>)
CEXP u64 ringcnt4(G CR g) NE {
  const u32 n = g.size();
  G dg(n), dgv(n);
  flt_ (u32, u, 0, n)
    for (auto v : g[u]) (std::make_pair(g[u].size(), u) < std::make_pair(g[(u32)v].size(), (u32)v) ? dg : dgv).add_arc(u, (u32)v);
  dg.build(), dgv.build();
  return ringcnt4_impl_::run(dg, dgv);
}

}  // namespace tifa_libs::graph

#endif