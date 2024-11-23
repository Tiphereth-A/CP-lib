#ifndef TIFALIBS_POLY_INV_FPS
#define TIFALIBS_POLY_INV_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto inv_fps(poly<ccore, mint, args...> CR p, u32 n = 0) {
  if (assert(p[0] != 0); !n) n = (u32)p.size();
  poly<ccore, mint, args...> a{p[0].inv()};
  for (u32 i = 1; i < n; i *= 2) a = (a * 2 - (a * a * p).pre(i * 2)).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs::math

#endif