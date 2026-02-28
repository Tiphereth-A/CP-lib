#ifndef TIFALIBS_FPS_ASIN_LIB
#define TIFALIBS_FPS_ASIN_LIB

#include "../ln/lib.hpp"
#include "../sqrt/lib.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto asin_fps(poly<ccore, mint, args...> CR p) NE {
  const mint i = qpow(poly<ccore, mint, args...>::conv_core.G, (mint::mod() - 1) / 4);
  return ln_fps(sqrt_fps(-p * p + 1, (u32)p.size()).value() + i * p) * -i;
}

}  // namespace tifa_libs::math

#endif