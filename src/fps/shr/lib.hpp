#pragma once

#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {

CEXP auto shr_fps(poly_c auto CR p, usz x) NE {
  retif_((!x) [[unlikely]], p);
  auto _ = p;
  fill(std::shift_left(begin(_), end(_), (isz)x), end(_), 0);
  return _;
}
CEXP auto shr_strip_fps(poly_c auto CR p, usz x) NE {
  auto _ = p;
  _.erase(std::shift_left(begin(_), end(_), (isz)x), end(_));
  return _;
}

}  // namespace tifa_libs
