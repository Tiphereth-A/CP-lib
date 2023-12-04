#ifndef TIFALIBS_POLY_POLY_TAN
#define TIFALIBS_POLY_POLY_TAN

#include "../math/proot_u64.hpp"
#include "../math/qpow.hpp"
#include "poly_exp.hpp"
#include "poly_inv.hpp"

namespace tifa_libs::math {

template <class T>
poly<T> poly_tan(poly<T> const &p) {
  using mint = typename T::value_type;
  mint i = -qpow(mint(proot_u64(mint::mod())), (mint::mod() - 1) / 4);
  auto _ = poly_exp(p * i), _0 = _ - 1, _1 = _ + 1;
  _0 = _0.conv(poly_inv(_1) * i);
  _0.resize(p.size());
  return _0;
}

}  // namespace tifa_libs::math

#endif