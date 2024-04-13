#ifndef TIFALIBS_GRAPH_CLE
#define TIFALIBS_GRAPH_CLE

#include "../ds/dsu_basic.hpp"
#include "../ds/skew_heap.hpp"

namespace tifa_libs::graph {

// edge: {w, u, v}
template <class T>
constexpr vec<std::tuple<T, u32, u32>> cle(u32 n, u32 root, vec<std::tuple<T, u32, u32>> const &arcs) {
  ds::SkewHeap<T> heap;
  ds::dsu_basic<> uf(n);
  vec<u32> used(n, -1_u32), from(n), come(n, -1_u32);
  vec<T> from_cost(n);

  used[root] = root;
  vec<u32> par_e(arcs.size(), -1_u32), stem(n, -1_u32), idxs;

  for (u32 i = 0; i < arcs.size(); ++i) {
    auto [w, u, v] = arcs[i];
    come[v] = heap.push(come[v], w, i);
  }

  T costs = 0;
  for (u32 start = 0; start < n; start++) {
    if (~used[start]) continue;
    u32 now = start;
    vec<u32> chi_e;
    u32 cycle = 0;
    while (!~used[now] || used[now] == start) {
      used[now] = start;
      auto &node = heap.d[come[now]];
      if (!~come[now]) return {};
      u32 src = (u32)uf.find(std::get<1>(arcs[node.idx]));
      T cost = heap.weight(come[now]);
      u32 idx = node.idx;
      come[now] = heap.pop(come[now]);
      if (src == now) continue;

      from[now] = src, from_cost[now] = cost;
      if (!~stem[now]) stem[now] = idx;
      costs += cost;
      idxs.push_back(idx);
      while (cycle) {
        par_e[chi_e.back()] = idx;
        chi_e.pop_back();
        --cycle;
      }
      chi_e.push_back(idx);

      if (used[src] == start) {
        u32 p = now;
        do {
          if (~come[p]) heap.apply(come[p], -from_cost[p]);
          if (p != now) {
            uf.merge(p, now);
            u32 newheap = heap.merge(come[now], come[p]);
            come[now = (u32)uf.find(now)] = newheap;
          }
          p = (u32)uf.find(from[p]);
          ++cycle;
        } while (p != now);
      } else now = src;
    }
  }

  vec<u32> used_e(arcs.size());
  vec<std::tuple<T, u32, u32>> res;
  for (u32 _ = (u32)idxs.size(); _--;) {
    u32 idx = idxs[_];
    if (used_e[idx]) continue;
    auto [w, u, v] = arcs[idx];
    res.push_back(arcs[idx]);
    u32 x = stem[v];
    while (x != idx) used_e[x] = true, x = par_e[x];
  }
  return res;
}

}  // namespace tifa_libs::graph

#endif