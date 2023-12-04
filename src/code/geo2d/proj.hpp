#ifndef TIFALIBS_GEO2D_PROJ
#define TIFALIBS_GEO2D_PROJ

#include "line.hpp"

namespace tifa_libs::geo {

// projection to a line
template <class FP>
constexpr point<FP> proj(line<FP> const &l, point<FP> const &p) {
  point dir = l.direction();
  return l.l + dir * (dir * (p - l.l) / dir.norm2());
}
// reflection about a line
template <class FP>
constexpr point<FP> reflect(line<FP> const &l, point<FP> const &p) { return proj(l, p) * 2 - p; }

}  // namespace tifa_libs::geo

#endif