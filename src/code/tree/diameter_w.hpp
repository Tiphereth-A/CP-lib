#ifndef TIFA_LIBS_TREE_DIAMETER_W
#define TIFA_LIBS_TREE_DIAMETER_W

#include "tree.hpp"
#include "tree_dis.hpp"

namespace tifa_libs::graph {

// {u, v, diam}
template <class T>
inline std::tuple<u32, u32, T> tree_diameter_w(tree<T> &tr) {
  static_assert(!std::is_void_v<T>);
  auto _ = tr.rt;
  auto d = tree_dis(tr);
  u32 u = tr.rt = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  d = tree_dis(tr);
  u32 v = (u32)std::distance(d.begin(), std::max_element(d.begin(), d.end()));
  tr.rt = _;
  return {u, v, d[v]};
}

}  // namespace tifa_libs::graph

#endif