#ifndef TIFALIBS_POLY_POW_FPS
#define TIFALIBS_POLY_POW_FPS

#include "../math/qpow.hpp"
#include "exp_fps.hpp"
#include "ln_fps.hpp"
#include "shl_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> pow_fps(poly<mint, ccore> CR p, u64 y, u32 n = 0) {
  if (!n) n = p.size();
  if (y == 0) {
    poly<mint, ccore> _(n);
    if (n) _[0] = 1;
    return _;
  }
  if (y == 1) return p;
  u32 l0 = u32(std::ranges::find_if(p.data(), [](cT_(mint) x) { return x != 0; }) - p.data().begin());
  if ((u128)l0 * y >= n) return poly<mint, ccore>(n);
  if (l0) {
    auto _ = shr_fps(p, l0), g = pow_fps(_, y, u32(n - l0 * y));
    return g.resize(n), shl_fps(g, l0 * y);
  }
  auto _ = p;
  mint _0 = p[0];
  if (_0 != 1) _ *= _0.inv();
  if (_ = exp_fps(ln_fps(_) * y); _0 != 1) _ *= qpow(_0, y);
  return _.pre(n);
}

}  // namespace tifa_libs::math

#endif