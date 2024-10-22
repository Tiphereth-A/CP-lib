#ifndef TIFALIBS_POLY_INV_FPS
#define TIFALIBS_POLY_INV_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> inv_fps(poly<mint, ccore> CR p, u32 n = 0) {
  if (assert(p[0] != 0); !n) n = p.size();
  poly<mint, ccore> a{p[0].inv()};
  for (u32 i = 1; i < n; i *= 2) a = (a * 2 - (a * a * p).pre(i * 2)).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs::math

#endif