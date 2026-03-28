#pragma once

#include "../div/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto divmod_fps(poly_t CR p, poly_t CR q) NE {
  const u32 n = (u32)p.size(), m = (u32)q.size();
  if (n < m) return std::make_pair(poly_t{}, p);
  auto d = div_fps(p, q);
  d.strip();
  auto r = d;
  r.conv(q), r.resize(m - 1), (r = p - r).resize(m - 1), r.strip();
  return std::make_pair(d, r);
}

}  // namespace tifa_libs
