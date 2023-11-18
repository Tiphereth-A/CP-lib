#ifndef TIFALIBS_POLYSP_MAKE
#define TIFALIBS_POLYSP_MAKE

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
using polysp = vec<std::pair<u32, typename poly<T>::value_type>>;

template <class T>
polysp<T> poly2sp(poly<T> const& p, u32 n = 0) {
  if (!n) n = p.size();
  polysp<T> fs;
  for (u32 i = 0; i < n; ++i)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif