#pragma once

#include "../../../util/traits/math/lib.hpp"
#include "../../ds/amat/lib.hpp"

namespace tifa_libs {

//! will change input graph
// @return false if invalid (has negative cycle), otherwise true
template <class T>
CEXP bool floyd(amat<T>& g, T INF = inf_v<T>) NE {
  const u32 n = g.vsize();
  flt_ (u32, k, 0, n)
    flt_ (u32, x, 0, n)
      if (g.val(x, k) < INF)
        flt_ (u32, y, 0, n)
          if (g.val(k, y) < INF) g.set_val(x, y, min(g.val(x, y), g.val(x, k) + g.val(k, y)));
  if CEXP (sint_c<T>)
    flt_ (u32, x, 0, n)
      if (g.val(x, x) < 0) return 0;
  return 1;
}

}  // namespace tifa_libs
