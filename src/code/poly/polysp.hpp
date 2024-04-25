#ifndef TIFALIBS_POLY_POLYSP
#define TIFALIBS_POLY_POLYSP

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint>
using polysp = vec<std::pair<u32, mint>>;

template <class mint, class ccore>
CEXP polysp<mint> poly2sp(poly<mint, ccore> CR p, u32 n = 0) {
  if (!n) n = p.size();
  polysp<mint> fs;
  flt_ (u32, i, 0, n)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif