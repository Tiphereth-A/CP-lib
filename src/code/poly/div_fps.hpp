#ifndef TIFALIBS_POLY_DIV_FPS
#define TIFALIBS_POLY_DIV_FPS

#include "inv_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> div_fps(poly<mint, ccore> p, poly<mint, ccore> q) {
  const u32 n = p.size(), m = q.size();
  if (n < m) return poly<mint, ccore>{};
  p.reverse(), q.reverse(), q.resize(n - m + 1), p.conv(inv_fps(q)), p.resize(n - m + 1), p.reverse();
  return p;
}

}  // namespace tifa_libs::math

#endif