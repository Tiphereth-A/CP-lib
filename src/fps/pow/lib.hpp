#pragma once

#include "../../math/qpow/basic/lib.hpp"
#include "../exp/lib.hpp"
#include "../ln/lib.hpp"
#include "../shl/lib.hpp"
#include "../shr/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto pow_fps(poly_t CR p, u64 y, u32 n = 0) NE {
  using mint = TPN poly_t::val_t;
  if (!n) n = (u32)p.size();
  if (y == 0) {
    poly_t _(n);
    if (n) _[0] = 1;
    return _;
  }
  if (y == 1) return p;
  u32 l0 = u32(find_if(p, [](cT_(mint) x) NE { return x != 0; }) - begin(p));
  if ((u128)l0 * y >= n) return poly_t(n);
  if (l0) {
    auto _ = shr_fps(p, l0), g = pow_fps(_, y, u32(n - l0 * y));
    g.resize(n);
    return shl_fps(g, l0 * y);
  }
  auto _ = p;
  mint _0 = p[0];
  if (_0 != 1) _ *= _0.inv();
  if (_ = exp_fps(ln_fps(_) * y); _0 != 1) _ *= qpow(_0, y);
  return _.pre(n);
}

}  // namespace tifa_libs
