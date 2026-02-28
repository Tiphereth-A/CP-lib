#ifndef TIFALIBS_FPSSP_POLYSP_LIB
#define TIFALIBS_FPSSP_POLYSP_LIB

#include "../../fps/ds/poly/lib.hpp"

namespace tifa_libs::math {

template <class mint>
using polysp = vec<std::pair<u32, mint>>;

template <template <class... Ts> class ccore, class mint, class... args>
CEXP polysp<mint> poly2sp(poly<ccore, mint, args...> CR p, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  polysp<mint> fs;
  flt_ (u32, i, 0, n)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs::math

#endif