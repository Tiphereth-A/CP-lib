#ifndef TIFALIBS_POLY_POLY_DIV
#define TIFALIBS_POLY_POLY_DIV

#include "poly_inv.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_div(poly p, poly q) {
  u32 n = p.size(), m = q.size();
  if (n < m) return poly();
  p.reverse();
  q.reverse();
  q.resize(n - m + 1);
  p.conv(poly_inv(q));
  p.resize(n - m + 1);
  p.reverse();
  return p;
}

}  // namespace tifa_libs::math

#endif