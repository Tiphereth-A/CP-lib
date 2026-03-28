#pragma once

#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

CEXP auto shl_fps(poly_c auto CR p, usz x) NE {
  retif_((!x) [[unlikely]], p);
  auto _ = p;
  fill(begin(_), std::shift_right(begin(_), end(_), (isz)x), 0);
  return _;
}

}  // namespace tifa_libs
