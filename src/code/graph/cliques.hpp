#ifndef TIFALIBS_GRAPH_CLIQUES
#define TIFALIBS_GRAPH_CLIQUES

#include "../util/util.hpp"

namespace tifa_libs::graph {

// enumerate all maximal cliques
// @param P possibly in clique
// @param X not in clique
// @param R in clique
template <usz N, class F>
requires requires(F f, std::bitset<N> R) { f(R); }
CEXP void cliques(u32 n, arr<std::bitset<N>, N> CR adj, F&& f) {
  using B = std::bitset<N>;
  auto g = [&](auto&& g, B P, B X, B R) -> void {
    if (P.none()) {
      if (X.none()) f(R);
      return;
    }
    B _ = P & ~adj[(P | X)._Find_first()];
    flt_ (u32, i, 0, n)
      if (_[i]) {
        R[i] = 1;
        g(g, P & adj[i], X & adj[i], R);
        R[i] = P[i] = 0;
        X[i] = 1;
      }
  };
  g(g, ~B(), B(), B());
}

}  // namespace tifa_libs::graph

#endif