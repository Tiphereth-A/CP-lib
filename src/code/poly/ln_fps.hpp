#ifndef TIFALIBS_POLY_LN_FPS
#define TIFALIBS_POLY_LN_FPS

#include "deriv_fps.hpp"
#include "int_fps.hpp"
#include "inv_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto ln_fps(poly<ccore, mint, args...> CR p, u32 n = 0) NE {
  if (assert(p[0] == 1); !n) n = (u32)p.size();
  auto _ = deriv_fps(p).pre(n);
  _.conv(inv_fps(p, n));
  return int_fps(_).pre(n);
}

}  // namespace tifa_libs::math

#endif