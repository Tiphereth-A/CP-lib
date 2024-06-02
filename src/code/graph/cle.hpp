#ifndef TIFALIBS_GRAPH_CLE
#define TIFALIBS_GRAPH_CLE

#include "../ds/dsu_basic.hpp"
#include "../ds/skew_heap.hpp"

namespace tifa_libs::graph {

// edge: {w, u, v}
template <class T>
CEXP vec<std::tuple<T, u32, u32>> cle(u32 n, u32 root, vec<std::tuple<T, u32, u32>> CR arcs) {
  ds::skew_heap<T> heap;
  ds::dsu_basic<> uf(n);
  vecu used(n, -1_u32), from(n), come(n, -1_u32);
  vec<T> from_cost(n);
  used[root] = root;
  vecu par_e(arcs.size(), -1_u32), stem(n, -1_u32), idxs;
  flt_ (u32, i, 0, (u32)arcs.size()) {
    auto [w, u, v] = arcs[i];
    come[v] = heap.push(come[v], w, i);
  }
  T costs = 0;
  flt_ (u32, start, 0, n) {
    if (~used[start]) continue;
    u32 now = start;
    vecu chi_e;
    u32 cyc = 0;
    while (!~used[now] || used[now] == start) {
      used[now] = start;
      auto &node = heap.d[come[now]];
      if (!~come[now]) return {};
      u32 src = (u32)uf.find(std::get<1>(arcs[node.idx]));
      T cost = heap.weight(come[now]);
      u32 idx = node.idx;
      if (come[now] = heap.pop(come[now]); src == now) continue;
      if (from[now] = src, from_cost[now] = cost; !~stem[now]) stem[now] = idx;
      costs += cost, idxs.push_back(idx);
      while (cyc) par_e[chi_e.back()] = idx, chi_e.pop_back(), --cyc;
      if (chi_e.push_back(idx); used[src] == start) {
        u32 p = now;
        do {
          if (~come[p]) heap.apply(come[p], -from_cost[p]);
          if (p != now) {
            uf.merge(p, now);
            u32 newheap = heap.merge(come[now], come[p]);
            come[now = (u32)uf.find(now)] = newheap;
          }
          p = (u32)uf.find(from[p]), ++cyc;
        } while (p != now);
      } else now = src;
    }
  }

  vecu vis_e(arcs.size());
  vec<std::tuple<T, u32, u32>> res;
  for (u32 _ = (u32)idxs.size(); _--;) {
    const u32 i = idxs[_];
    if (vis_e[i]) continue;
    auto [w, u, v] = arcs[i];
    res.push_back(arcs[i]);
    u32 x = stem[v];
    while (x != i) vis_e[x] = true, x = par_e[x];
  }
  return res;
}

}  // namespace tifa_libs::graph

#endif