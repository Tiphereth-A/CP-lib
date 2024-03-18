#ifndef TIFALIBS_POLY_POLY_MODINV
#define TIFALIBS_POLY_POLY_MODINV

#include "poly_gcd.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr std::optional<poly> poly_modinv(poly const &f, poly const &g) {
  auto m = poly_gcd_impl_::pgcd_(f, g);
  if (poly _ = (m * ptt<poly>{f, g}).first; _.size() != 1) return {};
  else {
    auto __ = poly_divmod((m * ptt<poly>(poly(1, 1), g)).first, g);
    return __.second * _[0].inv();
  }
}

}  // namespace tifa_libs::math

#endif