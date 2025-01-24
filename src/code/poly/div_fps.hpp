#ifndef TIFALIBS_POLY_DIV_FPS
#define TIFALIBS_POLY_DIV_FPS

#include "inv_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto div_fps(poly<ccore, mint, args...> p, poly<ccore, mint, args...> q) NE {
  const u32 n = (u32)p.size(), m = (u32)q.size();
  if (n < m) return poly<ccore, mint, args...>{};
  p.reverse(), q.reverse();
  q.resize(n - m + 1), p.conv(inv_fps(q));
  p.resize(n - m + 1), p.reverse();
  return p;
}

}  // namespace tifa_libs::math

#endif