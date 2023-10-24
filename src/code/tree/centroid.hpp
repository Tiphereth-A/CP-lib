#ifndef TIFA_LIBS_TREE_CENTROID
#define TIFA_LIBS_TREE_CENTROID

#include "tree.hpp"

namespace tifa_libs::graph {

namespace tree_centroid_impl_ {

template <class T>
void dfs_(tree<T> &tr, vec<u32> &ans, u32 now, u32 fa) {
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

template <class T>
vec<u32> tree_centroid(tree<T> &tr) {
  tr.sz.resize(tr.v_size());
  vec<u32> ans;
  dfs_(tr, ans, tr.rt, tr.rt);
  return ans;
}

}  // namespace tree_centroid_impl_

using tree_centroid_impl_::tree_centroid;

}  // namespace tifa_libs::graph

#endif