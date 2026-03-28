#pragma once

#include "../inv/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto div_fps(poly_t p, poly_t q) NE {
  const u32 n = (u32)p.size(), m = (u32)q.size();
  if (n < m) return poly_t{};
  p.reverse(), q.reverse();
  q.resize(n - m + 1), p.conv(inv_fps(q));
  p.resize(n - m + 1), p.reverse();
  return p;
}

}  // namespace tifa_libs
