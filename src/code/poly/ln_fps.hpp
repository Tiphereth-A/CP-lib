#ifndef TIFALIBS_POLY_LN_FPS
#define TIFALIBS_POLY_LN_FPS

#include "deriv_fps.hpp"
#include "int_fps.hpp"
#include "inv_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> ln_fps(poly<mint, ccore> CR p, u32 n = 0) {
  if (assert(p[0] == 1); !n) n = p.size();
  auto _ = deriv_fps(p).pre(n);
  return _.conv(inv_fps(p, n)), int_fps(_).pre(n);
}

}  // namespace tifa_libs::math

#endif