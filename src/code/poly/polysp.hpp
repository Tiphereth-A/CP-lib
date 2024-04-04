#ifndef TIFALIBS_POLY_POLYSP
#define TIFALIBS_POLY_POLYSP

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint>
using polysp = vec<std::pair<u32, mint>>;

template <class mint, class ccore>
constexpr polysp<mint> poly2sp(poly<mint, ccore> const& p, u32 n = 0) {
  if (!n) n = p.size();
  polysp<mint> fs;
  for (u32 i = 0; i < n; ++i)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif