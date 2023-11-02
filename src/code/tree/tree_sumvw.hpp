#ifndef TIFA_LIBS_TREE_TREE_SUMVW
#define TIFA_LIBS_TREE_TREE_SUMVW

#include "tree.hpp"

namespace tifa_libs::graph {

namespace tree_sumvw_impl_ {

template <class VW, class EW>
void dfs_(tree<VW, EW> const &tr, vec<VW> &sumvw, u32 now, u32 fa) {
  sumvw[now] = tr.v_weight()[now];
  for (auto [to, w] : tr[now])
    if (to != fa) {
      sumvw[to] = sumvw[now] + w;
      dfs_(tr, sumvw, to, now);
      sumvw[now] += sumvw[to];
    }
}

}  // namespace tree_sumvw_impl_

template <class VW, class EW>
inline vec<VW> tree_sumvw(tree<VW, EW> const &tr) {
  static_assert(!std::is_void_v<VW>);
  vec<VW> sumvw(tr.v_size());
  tree_sumvw_impl_::dfs_(tr, sumvw, tr.rt, tr.v_size());
  return sumvw;
}

}  // namespace tifa_libs::graph

#endif