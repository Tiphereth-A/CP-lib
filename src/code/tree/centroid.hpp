#ifndef TIFA_LIBS_TREE_CENTROID
#define TIFA_LIBS_TREE_CENTROID

#include "tree.hpp"

namespace tifa_libs::graph {

namespace tree_centroid_impl_ {

template <class VW, class EW>
void dfs_(tree<VW, EW> &tr, vec<u32> &ans, u32 now, u32 fa) {
  tr.sz[now] = 1;
  u32 max_sz = 0;
  for (auto v : tr[now])
    if (v.to != fa) {
      dfs_(tr, ans, v.to, now);
      tr.sz[now] += tr.sz[v.to];
      max_sz = std::max(max_sz, tr.sz[v.to]);
    }
  if (std::max(max_sz, tr.v_size() - tr.sz[now]) <= tr.v_size() / 2) ans.push_back(now);
}

}  // namespace tree_centroid_impl_

template <class VW, class EW>
inline vec<u32> tree_centroid(tree<VW, EW> &tr) {
  tr.sz = vec<u32>(tr.v_size());
  vec<u32> ans;
  tree_centroid_impl_::dfs_(tr, ans, tr.rt, tr.v_size());
  return ans;
}

}  // namespace tifa_libs::graph

#endif