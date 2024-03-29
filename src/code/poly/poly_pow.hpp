#ifndef TIFALIBS_POLY_POLY_POW
#define TIFALIBS_POLY_POLY_POW

#include "../math/qpow.hpp"
#include "poly_exp.hpp"
#include "poly_ln.hpp"
#include "poly_shl.hpp"
#include "poly_shr.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_pow(poly const &p, u64 y, u32 n = 0) {
  using mint = typename poly::value_type;
  if (!n) n = p.size();
  if (y == 0) {
    poly _(n);
    if (n) _[0] = 1;
    return _;
  }
  if (y == 1) return p;
  u32 l0 = u32(std::find_if(p.data().begin(), p.data().end(), [](auto const &x) { return x != 0; }) - p.data().begin());
  if ((u128)l0 * y >= n) return poly(n);
  if (l0) {
    auto _ = poly_shr(p, l0), g = poly_pow(_, y, u32(n - l0 * y));
    g.resize(n);
    return poly_shl(g, l0 * y);
  }
  auto _ = p;
  mint _0 = p[0];
  if (_0 != 1) _ *= _0.inv();
  _ = poly_exp(poly_ln(_) * y);
  if (_0 != 1) _ *= qpow(_0, y);
  _.resize(n);
  return _;
}

}  // namespace tifa_libs::math

#endif