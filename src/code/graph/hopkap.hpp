#ifndef TIFALIBS_GRAPH_HOPKAP
#define TIFALIBS_GRAPH_HOPKAP

#include "../util/util.hpp"

namespace tifa_libs::graph {

// @param l number of vertex in left side
// @param r number of vertex in right side
// @param e arc from left to right
inline vecptu hopkap(u32 l, u32 r, vecptu CR e) NE {
  vvecu adj(l);
  vecu pre(r, -1_u32), nxt(l, -1_u32);
  for (auto [u, v] : e) adj[u].push_back(v);
  while (1) {
    vecu lev(l), ptr(l);
    u32 max_lev = 0;
    std::queue<u32> q;
    flt_ (u32, i, 0, l)
      if (!~nxt[i]) lev[i] = 1, q.push(i);
    while (!q.empty()) {
      u32 x = q.front();
      for (q.pop(); u32 y : adj[x])
        if (u32 z = pre[y]; !~z) max_lev = lev[x];
        else if (!lev[z]) lev[z] = lev[x] + 1, q.push(z);
      if (max_lev) break;
    }
    if (!max_lev) break;
    flt_ (u32, i, 0, l)
      if (lev[i] > max_lev) lev[i] = 0;
    auto f = [&](auto&& f, u32 x) NE -> bool {
      for (; ptr[x] < adj[x].size(); ++ptr[x])
        if (u32 y = adj[x][ptr[x]], z = pre[y]; !~z || (lev[z] == lev[x] + 1 && f(f, z))) {
          nxt[x] = y, pre[y] = x, ptr[x] = (u32)adj[x].size();
          return 1;
        }
      return 0;
    };
    flt_ (u32, i, 0, l)
      if (!~nxt[i]) f(f, i);
  }
  vecptu ans;
  flt_ (u32, i, 0, l)
    if (~nxt[i]) ans.emplace_back(i, nxt[i]);
  return ans;
}

}  // namespace tifa_libs::graph

#endif