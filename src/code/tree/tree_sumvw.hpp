#ifndef TIFALIBS_TREE_TREE_SUMVW
#define TIFALIBS_TREE_TREE_SUMVW

#include "../graph/dfs.hpp"

namespace tifa_libs::graph {

template <class G, class T>
CEXP vec<T> tree_sumvw(G CR tr, vec<T> CR v_weight) {
  vec<T> sumvw = v_weight;
  return dfs(tr, tr.root, fn_0, fn_0, [&](u32 to, u32 u, u32 = 1) { sumvw[u] += sumvw[to]; }, fn_0), sumvw;
}

}  // namespace tifa_libs::graph

#endif