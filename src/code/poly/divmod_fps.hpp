#ifndef TIFALIBS_POLY_DIVMOD_FPS
#define TIFALIBS_POLY_DIVMOD_FPS

#include "div_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
constexpr ptt<poly<mint, ccore>> divmod_fps(poly<mint, ccore> const &p, poly<mint, ccore> const &q) {
  u32 n = p.size(), m = q.size();
  if (n < m) return {poly<mint, ccore>{}, p};
  auto d = div_fps(p, q);
  d.strip();
  auto r = d;
  r.conv(q), r.resize(m - 1);
  r = p - r;
  r.resize(m - 1), r.strip();
  return {d, r};
}

}  // namespace tifa_libs::math

#endif