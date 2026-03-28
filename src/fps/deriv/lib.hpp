#pragma once

#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

CEXP auto deriv_fps(poly_c auto CR p) NE {
  auto _ = p;
  flt_ (u32, i, 1, (u32)_.size()) _[i - 1] = _[i] * i;
  _.back() = 0;
  return _;
}

}  // namespace tifa_libs
