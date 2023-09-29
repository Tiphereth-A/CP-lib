#ifndef TIFALIBS_POLY_SIN
#define TIFALIBS_POLY_SIN

#include "../math/proot_u64.hpp"
#include "../math/qpow.hpp"
#include "poly_exp.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_sin(poly<T> const &p) {
  using mint = typename T::value_type;
  mint i = qpow(mint(proot_u64(mint::mod())), (mint::mod() - 1) / 4);
  auto _ = p * i;
  return (poly_exp(_ * (mint::mod() - 1)) - poly_exp(_)) * i * ((mint::mod() + 1) / 2);
}

}  // namespace tifa_libs::math

#endif