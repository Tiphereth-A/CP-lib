#ifndef TIFA_LIBS_TREE_DIAMETER
#define TIFA_LIBS_TREE_DIAMETER

#include "tree.hpp"
#include "tree_dis.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class VW, class EW>
inline std::tuple<u32, u32, std::conditional_t<!tree<VW, EW>::HAS_EW, u32, EW>> tree_diameter(tree<VW, EW> &tr) {
  using tree_t = tree<VW, EW>;
  auto _ = tr.rt;
  vec<std::conditional_t<!tree_t::HAS_EW, u32, EW>> d(tr.v_size());
  if constexpr (!tree_t::HAS_EW) {
    tr.template reset_dfs_info<s_dep>();
    d = tr.dep;
  } else d = tree_dis(tr);
  u32 u = tr.rt = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  if constexpr (!tree_t::HAS_EW) {
    tr.template reset_dfs_info<s_dep>();
    d = tr.dep;
  } else d = tree_dis(tr);
  u32 v = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  tr.rt = _;
  return {u, v, d[v]};
}

}  // namespace tifa_libs::graph

#endif