#ifndef TIFA_LIBS_TREE_TREE_DIS
#define TIFA_LIBS_TREE_TREE_DIS

#include "tree.hpp"

namespace tifa_libs::graph {

namespace tree_dis_impl_ {

template <class T>
void dfs_(tree<T> const &tr, vec<T> &dis, u32 now, u32 fa) {
  for (auto [to, w] : tr[now])
    if (to != fa) {
      dis[to] = dis[now] + w;
      dfs_(tr, dis, to, now);
    }
}

template <class T>
inline vec<T> tree_dis(tree<T> const &tr) {
  static_assert(!std::is_void_v<T>);
  vec<T> dis(tr.v_size());
  dfs_(tr, dis, tr.rt, tr.v_size());
  return dis;
}

}  // namespace tree_dis_impl_

using tree_dis_impl_::tree_dis;

}  // namespace tifa_libs::graph

#endif