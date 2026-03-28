#pragma once

#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

template <poly_c poly_t>
CEXP auto int_fps(poly_t CR p) NE {
  auto _ = p;
  for (u32 i = (u32)_.size() - 1; i; --i) _[i] = _[i - 1] * TPN poly_t::val_t(i).inv();
  _[0] = 0;
  return _;
}

}  // namespace tifa_libs
