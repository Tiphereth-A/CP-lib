#pragma once

#include "../ds/graph_c/lib.hpp"

namespace tifa_libs {

template <graph_c G>
CEXP auto make_graphr(G CR g) NE {
  const u32 n = g.vsize();
  G ret(n);
  flt_ (u32, u, 0, n) g.foreach(u, [&](u32 v, auto&&... args) NE { ret.add_arc(v, u, std::forward<decltype(args)>(args)...); });
  ret.build();
  return ret;
}

}  // namespace tifa_libs
