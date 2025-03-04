#ifndef TIFALIBS_GRAPH_MIN_CYCLE_MEAN
#define TIFALIBS_GRAPH_MIN_CYCLE_MEAN

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::graph {

template <class T>
CEXP T min_cycle_mean(vec<edge_t<T>> CR edges, u32 n, T INF = inf_v<T>) NE {
  vec<T> d(n + 1), d2(n + 1);
  for (u32 i = 0; i < n; ++i, std::swap(d, d2))
    for (fill_n(d.begin(), n, INF); auto [w, u, v] : edges) d[v] = min(d[v], d2[u] + w);
  vec<T> dn = d2, mx(n + 1);
  T ans = INF;
  transform(dn, mx.begin(), [&](auto x) NE { return x / n; });
  fill(d2, 0);
  for (u32 i = 1; i < n; ++i, std::swap(d, d2)) {
    for (fill_n(d.begin(), n, INF); auto [w, u, v] : edges) d[v] = min(d[v], d2[u] + w);
    flt_ (u32, j, 0, n) mx[j] = max(mx[j], (dn[j] - d[j]) / (n - i));
  }
  flt_ (u32, i, 0, n)
    if (dn[i] < INF) ans = min(ans, mx[i]);
  return ans;
}

}  // namespace tifa_libs::graph

#endif