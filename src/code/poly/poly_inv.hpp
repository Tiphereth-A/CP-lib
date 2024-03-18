#ifndef TIFALIBS_POLY_POLY_INV
#define TIFALIBS_POLY_POLY_INV

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_inv(poly const &p, u32 n = 0) {
  assert(p[0] != 0);
  if (!n) n = p.size();
  poly a{p[0].inv()};
  for (u32 i = 1; i < n; i *= 2) a = (a * 2 - (a * a * p).pre(i * 2)).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs::math

#endif