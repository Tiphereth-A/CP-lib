#pragma once

#include "../ln/lib.hpp"
#include "../sqrt/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto asin_fps(poly_t CR p) NE {
  const auto i = qpow(p.conv_core.G, (poly_t::val_t::mod() - 1) / 4);
  return ln_fps(sqrt_fps(-p * p + 1, (u32)p.size()).value() + i * p) * -i;
}

}  // namespace tifa_libs
