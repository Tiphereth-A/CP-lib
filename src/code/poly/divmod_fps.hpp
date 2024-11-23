#ifndef TIFALIBS_POLY_DIVMOD_FPS
#define TIFALIBS_POLY_DIVMOD_FPS

#include "div_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto divmod_fps(poly<ccore, mint, args...> CR p, poly<ccore, mint, args...> CR q) {
  const u32 n = (u32)p.size(), m = (u32)q.size();
  if (n < m) return std::make_pair(poly<ccore, mint, args...>{}, p);
  auto d = div_fps(p, q);
  d.strip();
  auto r = d;
  r.conv(q), r.resize(m - 1), (r = p - r).resize(m - 1), r.strip();
  return std::make_pair(d, r);
}

}  // namespace tifa_libs::math

#endif