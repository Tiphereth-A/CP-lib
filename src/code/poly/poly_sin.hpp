#ifndef TIFALIBS_POLY_POLY_SIN
#define TIFALIBS_POLY_POLY_SIN

#include "../math/qpow.hpp"
#include "../nt/proot_u64.hpp"
#include "poly_exp.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_sin(poly const &p) {
  using mint = typename poly::value_type;
  mint i = qpow(mint(proot_u64(mint::mod())), (mint::mod() - 1) / 4);
  auto _ = p * i;
  return (poly_exp(_ * (mint::mod() - 1)) - poly_exp(_)) * i * ((mint::mod() + 1) / 2);
}

}  // namespace tifa_libs::math

#endif