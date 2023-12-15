#ifndef TIFALIBS_POLY_POLY_MODINV
#define TIFALIBS_POLY_POLY_MODINV

#include "poly_gcd.hpp"

namespace tifa_libs::math {

template <class T>
constexpr std::optional<poly<T>> poly_modinv(poly<T> const &f, poly<T> const &g) {
  auto m = poly_gcd_impl_::pgcd_(f, g);
  if (poly<T> _ = (m * ptt<poly<T>>{f, g}).first; _.size() != 1) return {};
  else {
    auto __ = poly_divmod((m * ptt<poly<T>>(poly<T>(1, 1), g)).first, g);
    return __.second * _[0].inv();
  }
}

}  // namespace tifa_libs::math

#endif