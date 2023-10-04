#ifndef TIFA_LIBS_GEO2D_PROJ
#define TIFA_LIBS_GEO2D_PROJ

#include "line.hpp"

namespace tifa_libs::geo2d {

// projection to a line
template <class FP>
constexpr point<FP> proj(line<FP> const &l1, point<FP> const &p) {
  point dir = l1.direction();
  return l1.l + dir * (dir * (p - l1.l) / dir.norm2());
}
// reflection about a line
template <class FP>
constexpr point<FP> reflect(line<FP> const &l1, point<FP> const &p) { return proj(l1, p) * 2 - p; }

}  // namespace tifa_libs::geo2d

#endif