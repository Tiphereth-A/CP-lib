#ifndef TIFALIBS_POLY_POLYSP
#define TIFALIBS_POLY_POLYSP

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
using polysp = vec<std::pair<u32, typename poly<T>::value_type>>;

template <class T>
constexpr polysp<T> poly2sp(poly<T> const& p, u32 n = 0) {
  if (!n) n = p.size();
  polysp<T> fs;
  for (u32 i = 0; i < n; ++i)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif