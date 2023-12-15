#ifndef TIFALIBS_TREE_TREE_SUMVW
#define TIFALIBS_TREE_TREE_SUMVW

#include "../graph/dfs.hpp"

namespace tifa_libs::graph {

template <class G, class T>
constexpr vec<T> tree_sumvw(G const &tr, vec<T> const &v_weight) {
  vec<T> sumvw(tr.g.size());
  dfs(
      tr, tr.root,
      [&](u32 u, u32) {
        sumvw[u] = v_weight[u];
      },
      [](u32, u32) {},
      [&](u32 to, u32 u) {
        sumvw[u] += sumvw[to];
      },
      [](u32, u32) {});
  return sumvw;
}

}  // namespace tifa_libs::graph

#endif