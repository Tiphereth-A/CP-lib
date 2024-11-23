#ifndef TIFALIBS_POLY_POLYSP
#define TIFALIBS_POLY_POLYSP

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint>
using polysp = vec<std::pair<u32, mint>>;

template <template <class... Ts> class ccore, class mint, class... args>
CEXP polysp<mint> poly2sp(poly<ccore, mint, args...> CR p, u32 n = 0) {
  if (!n) n = (u32)p.size();
  polysp<mint> fs;
  flt_ (u32, i, 0, n)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif