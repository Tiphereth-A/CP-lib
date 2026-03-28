#pragma once

#include "../ln/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto exp_fps(poly_t p, u32 n = 0) NE {
  if (assert(p[0] == 0); !n) n = (u32)p.size();
  p[0] += 1;
  poly_t a{1};
  for (u32 i = 1; i < n; i *= 2) a = (a * (p.pre(i * 2) - ln_fps(a, i * 2))).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs
