#ifndef TIFALIBS_POLY_EXP_FPS
#define TIFALIBS_POLY_EXP_FPS

#include "ln_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> exp_fps(poly<mint, ccore> p, u32 n = 0) {
  if (assert(p[0] == 0); !n) n = p.size();
  p[0] += 1;
  poly<mint, ccore> a{1};
  for (u32 i = 1; i < n; i *= 2) a = (a * (p.pre(i * 2) - ln_fps(a, i * 2))).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs::math

#endif