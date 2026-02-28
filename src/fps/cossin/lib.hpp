#ifndef TIFALIBS_FPS_COSSIN_LIB
#define TIFALIBS_FPS_COSSIN_LIB

#include "../../math/qpow/basic/lib.hpp"
#include "../exp/lib.hpp"

namespace tifa_libs::math {

// @return [cos(p(x)), sin(p(x))]
template <template <class... Ts> class ccore, class mint, class... args>
requires(ccore<mint, args...>::ct_cat == CCORE::NTT)
CEXP auto cossin_fps(poly<ccore, mint, args...> p, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  const mint i = qpow(poly<ccore, mint, args...>::conv_core.G, (mint::mod() - 1) / 4),
             inv2 = (mint::mod() + 1) / 2;
  (p *= i).resize(n);
  const auto expf = exp_fps(p), expnf = exp_fps(-p);
  return std::make_pair((expf + expnf) * inv2, (expnf - expf) * (i * inv2));
}

}  // namespace tifa_libs::math

#endif