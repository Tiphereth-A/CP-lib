#ifndef TIFALIBS_POLY_MODINV_FPS
#define TIFALIBS_POLY_MODINV_FPS

#include "gcd_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto modinv_fps(poly<ccore, mint, args...> CR f, poly<ccore, mint, args...> CR g) NE {
  using poly_t = poly<ccore, mint, args...>;
  std::optional<poly_t> ret;
  auto m = gcd_fps_impl_::pgcd_(f, g);
  poly_t _ = (m * ptt<poly_t>{f, g}).first;
  if (_.size() == 1) ret.emplace(divmod_fps((m * ptt<poly_t>(poly_t(1, 1), g)).first, g).second * _[0].inv());
  return ret;
}

}  // namespace tifa_libs::math

#endif