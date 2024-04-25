#ifndef TIFALIBS_POLY_ASIN_FPS
#define TIFALIBS_POLY_ASIN_FPS

#include "ln_fps.hpp"
#include "sqrt_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> asin_fps(poly<mint, ccore> CR p) {
  mint i = qpow(poly<mint, ccore>::conv_core.G, (mint::mod() - 1) / 4);
  return ln_fps(sqrt_fps(-p * p + 1, p.size()).value() + i * p) * -i;
}

}  // namespace tifa_libs::math

#endif