#ifndef TIFALIBS_FPS_ATAN_LIB
#define TIFALIBS_FPS_ATAN_LIB

#include "../deriv/lib.hpp"
#include "../int/lib.hpp"
#include "../inv/lib.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto atan_fps(poly<ccore, mint, args...> CR p) NE {
  const u32 n = (u32)p.size();
  auto _ = p;
  (_ *= _).resize(n), _[0] += 1;
  (_ = inv_fps(_) * deriv_fps(p)).resize(n);
  return int_fps(_);
}

}  // namespace tifa_libs::math

#endif