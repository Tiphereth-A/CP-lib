#ifndef TIFALIBS_POLYSP_MAKE
#define TIFALIBS_POLYSP_MAKE

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
using polysp = vec<std::pair<size_t, typename poly<T>::value_type>>;

template <class T>
inline polysp<T> poly2sp(poly<T> const& p, size_t n = 0) {
  assert(!p.data().empty() && p[0] != 0);
  if (!n) n = p.size();
  polysp<T> fs;
  for (size_t i = 0; i < p.size(); ++i)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif