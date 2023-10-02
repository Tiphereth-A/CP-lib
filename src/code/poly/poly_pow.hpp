#ifndef TIFALIBS_POLY_POW
#define TIFALIBS_POLY_POW

#include "../math/euler_phi_u64.hpp"
#include "../math/qpow.hpp"
#include "poly_exp.hpp"
#include "poly_ln.hpp"
#include "poly_shl.hpp"
#include "poly_shr.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_pow(poly<T> const &p, u64 y) {
  using mint = typename T::value_type;
  if (y == 1) return p;
  size_t y_ = y, n = p.size();
  size_t l0 = std::find_if(p.data().begin(), p.data().end(), [](auto const &x) { return x != 0; }) - p.data().begin();
  if (l0 > 0 && y > n / l0) return poly<T>(n);
  auto _ = p;
  if (y == 0) {
    std::fill(_.data().begin() + 1, _.data().end(), 0);
    _[0] = 1;
    return _;
  }
  if (u64 phi = euler_phi_u64(mint::mod()); y > phi) y = y % phi + phi;
  _ = poly_shl(_, l0);
  _.strip();
  mint _0 = _[0];
  if (_0 != 1) _ *= _0.inv();
  _ = poly_exp(poly_ln(_) * y);
  if (_0 != 1) _ *= qpow(_0, y);
  _.resize(n);
  poly_shr(_, l0 * y_);
  return _;
}

}  // namespace tifa_libs::math

#endif