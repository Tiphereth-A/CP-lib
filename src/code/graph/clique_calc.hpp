#ifndef TIFALIBS_GRAPH_CLIQUE_ALL
#define TIFALIBS_GRAPH_CLIQUE_ALL

#include "../util/util.hpp"

namespace tifa_libs::graph {

// calculate $\operatorname{sum}_{c\subseteq C} \operatorname{op}_{v\in c}$, which $C$ is set of all cliques (include $\varnothing$)
// @param e_sum identity element of @sum
// @param e_op identity element of @op
template <class T, usz N, class S, class OP>
requires requires(S sum, OP op, T val1, T val2, u32 v) {
  { sum(val1, val2) } -> std::same_as<T>;
  { op(val1, v) } -> std::same_as<T>;
}
CEXP T clique_calc(u32 n, arr<std::bitset<N>, N> CR adj, S&& sum, OP&& op, T e_sum = T(0), T e_op = T(1)) NE {
  using B = std::bitset<N>;
  B _{};
  T ans = e_sum;
  auto h = [&](auto&& h, u32 now, T t) NE -> void {
    ans = sum(ans, t);
    flt_ (u32, v, now + 1, n) {
      if ((_ & adj[v]).count() != _.count()) continue;
      _[v] = 1, h(h, v, op(t, v)), _[v] = 0;
    }
  };
  h(h, -1_u32, e_op);
  return ans;
}

}  // namespace tifa_libs::graph

#endif