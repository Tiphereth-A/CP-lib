#ifndef TIFA_LIBS_TREE_DIAMETER
#define TIFA_LIBS_TREE_DIAMETER

#include "tree.hpp"
#include "tree_dis.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class VW, class EW>
inline std::tuple<u32, u32, EW> tree_diameter(tree<VW, EW> &tr) {
  auto _ = tr.rt;
  vec<u32> d;
  if constexpr (std::is_void_v<EW>) d.resize(tr.v_size(), 1);
  else d = tree_dis(tr);
  u32 u = tr.rt = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  d = tree_dis(tr);
  u32 v = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  tr.rt = _;
  return {u, v, d[v]};
}

}  // namespace tifa_libs::graph

#endif