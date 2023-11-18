#ifndef TIFA_LIBS_TREE_TREE_SUMVW
#define TIFA_LIBS_TREE_TREE_SUMVW

#include "../graph/dfs.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

template <class T>
vec<T> tree_sumvw(tree const &tr, vec<T> const &v_weight) {
  vec<T> sumvw(tr.g.size());
  dfs(
      tr, tr.root,
      [&](u32 u, u32) {
        sumvw[u] = v_weight[u];
      },
      [](u32, u32) {},
      [&](u32 to, u32 u) {
        sumvw[u] += sumvw[to];
      });
  return sumvw;
}

}  // namespace tifa_libs::graph

#endif