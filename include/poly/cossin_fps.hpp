#ifndef TIFALIBS_POLY_COSSIN_FPS
#define TIFALIBS_POLY_COSSIN_FPS

#include "../math/qpow.hpp"
#include "exp_fps.hpp"

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