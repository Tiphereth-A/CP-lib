#pragma once

#include "../../math/qpow/basic/lib.hpp"
#include "../exp/lib.hpp"

namespace tifa_libs {

// @return [cos(p(x)), sin(p(x))]
template <poly_c poly_t>
requires(poly_t::ccore_t::ct_cat == CCORE::NTT)
CEXP auto cossin_fps(poly_t p, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  const auto i = qpow(poly_t::ccore_t::G, (poly_t::val_t::mod() - 1) / 4),
             inv2 = (poly_t::val_t::mod() + 1) / 2;
  (p *= i).resize(n);
  const auto expf = exp_fps(p), expnf = exp_fps(-p);
  return std::make_pair((expf + expnf) * inv2, (expnf - expf) * (i * inv2));
}

}  // namespace tifa_libs
