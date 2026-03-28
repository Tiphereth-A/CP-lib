#pragma once

#include "../gcd/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto modinv_fps(poly_t CR f, poly_t CR g) NE {
  std::optional<poly_t> ret;
  auto m = gcd_fps_impl_::pgcd_(f, g);
  poly_t _ = (m * ptt<poly_t>{f, g}).first;
  if (_.size() == 1) ret.emplace(divmod_fps((m * ptt<poly_t>(poly_t(1, 1), g)).first, g).second * _[0].inv());
  return ret;
}

}  // namespace tifa_libs
