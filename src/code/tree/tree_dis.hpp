#ifndef TIFA_LIBS_TREE_TREE_DIS
#define TIFA_LIBS_TREE_TREE_DIS

#include "tree.hpp"

namespace tifa_libs::graph {

namespace tree_dis_impl_ {

template <class VW, class EW>
void dfs_(tree<VW, EW> const &tr, vec<EW> &dis, u32 now, u32 fa) {
  for (auto [to, w] : tr[now])
    if (to != fa) {
      dis[to] = dis[now] + w;
      dfs_(tr, dis, to, now);
    }
}

}  // namespace tree_dis_impl_

template <class VW, class EW>
inline vec<EW> tree_dis(tree<VW, EW> const &tr) {
  static_assert(!std::is_void_v<EW>);
  vec<EW> dis(tr.v_size());
  tree_dis_impl_::dfs_(tr, dis, tr.rt, tr.v_size());
  return dis;
}

}  // namespace tifa_libs::graph

#endif