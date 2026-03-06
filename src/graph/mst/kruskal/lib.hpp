#pragma once

#include "../../../ds/dsu/basic/lib.hpp"
#include "../../../tree/ds/lib.hpp"

namespace tifa_libs::graph {

//! edges MUST be sorted
template <class T>
CEXP treew<T> kruskal(vec<edge_t<T>> sorted_a, u32 n) NE {
  treew<T> tr(n);
  ds::dsu_basic dsu(n);
  for (u32 m = n - 1; auto [w, u, v] : sorted_a) {
    if (dsu.merge(u, v)) tr.add_arc(u, v, w), tr.add_arc(v, u, w), --m;
    if (!m) break;
  }
  return tr;
}

}  // namespace tifa_libs::graph
