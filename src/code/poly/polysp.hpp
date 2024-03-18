#ifndef TIFALIBS_POLY_POLYSP
#define TIFALIBS_POLY_POLYSP

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class poly>
using polysp = vec<std::pair<u32, typename poly::value_type>>;

template <class poly>
constexpr polysp<poly> poly2sp(poly const& p, u32 n = 0) {
  if (!n) n = p.size();
  polysp<poly> fs;
  for (u32 i = 0; i < n; ++i)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif