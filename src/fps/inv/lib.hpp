#pragma once

#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto inv_fps(poly_t CR p, u32 n = 0) NE {
  if (assert(p[0] != 0); !n) n = (u32)p.size();
  poly_t a{p[0].inv()};
  for (u32 i = 1; i < n; i *= 2) a = (a * 2 - (a * a * p).pre(i * 2)).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs
