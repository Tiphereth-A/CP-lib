#ifndef TIFALIBS_POLY_MODINV_FPS
#define TIFALIBS_POLY_MODINV_FPS

#include "gcd_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
constexpr std::optional<poly<mint, ccore>> modinv_fps(poly<mint, ccore> const &f, poly<mint, ccore> const &g) {
  using poly_t = poly<mint, ccore>;
  auto m = gcd_fps_impl_::pgcd_(f, g);
  if (poly_t _ = (m * ptt<poly_t>{f, g}).first; _.size() != 1) return {};
  else {
    auto __ = divmod_fps((m * ptt<poly_t>(poly_t(1, 1), g)).first, g);
    return __.second * _[0].inv();
  }
}

}  // namespace tifa_libs::math

#endif