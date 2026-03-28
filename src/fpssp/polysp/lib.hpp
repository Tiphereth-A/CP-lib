#pragma once

#include "../../fps/ds/poly_c/lib.hpp"

namespace tifa_libs {

template <class mint>
using polysp = vec<std::pair<u32, mint>>;

template <poly_c poly_t>
CEXP auto poly2sp(poly_t CR p, u32 n = 0) NE {
  if (!n) n = (u32)p.size();
  polysp<TPN poly_t::val_t> fs;
  flt_ (u32, i, 0, n)
    if (p[i] != 0) fs.emplace_back(i, p[i]);
  return fs;
}

}  // namespace tifa_libs
