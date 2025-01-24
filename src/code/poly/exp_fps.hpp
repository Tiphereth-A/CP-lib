#ifndef TIFALIBS_POLY_EXP_FPS
#define TIFALIBS_POLY_EXP_FPS

#include "ln_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto exp_fps(poly<ccore, mint, args...> p, u32 n = 0) NE {
  if (assert(p[0] == 0); !n) n = (u32)p.size();
  p[0] += 1;
  poly<ccore, mint, args...> a{1};
  for (u32 i = 1; i < n; i *= 2) a = (a * (p.pre(i * 2) - ln_fps(a, i * 2))).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs::math

#endif