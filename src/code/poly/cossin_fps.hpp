#ifndef TIFALIBS_POLY_COSSIN_FPS
#define TIFALIBS_POLY_COSSIN_FPS

#include "../math/qpow.hpp"
#include "exp_fps.hpp"

namespace tifa_libs::math {

// @return [cos(p(x)), sin(p(x))]
template <class mint, class ccore>
requires(ccore::ct_cat == ct_NTT)
CEXP ptt<poly<mint, ccore>> cossin_fps(poly<mint, ccore> p, u32 n = 0) {
  if (!n) n = (u32)p.size();
  const mint i = qpow(poly<mint, ccore>::conv_core.G, (mint::mod() - 1) / 4), inv2 = (mint::mod() + 1) / 2;
  (p *= i).resize(n);
  const auto expf = exp_fps(p), expnf = exp_fps(-p);
  return {(expf + expnf) * inv2, (expnf - expf) * (i * inv2)};
}

}  // namespace tifa_libs::math

#endif