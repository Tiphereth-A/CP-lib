#ifndef TIFA_LIBS_GEO2D_ARGSORT
#define TIFA_LIBS_GEO2D_ARGSORT

#include "point.hpp"

namespace tifa_libs::geo {

// sort in counterclockwise
template <class FP>
inline void argsort(vec<point<FP>> &vp, u32 quad_start = 6) {
  assert(quad_start < 9);
  std::sort(vp.begin(), vp.end(), [ofs = 9 - quad_start](auto const &l, auto const &r) { return l.quad() == r.quad() ? is_pos(l ^ r) : (l.quad() + ofs) % 9 < (r.quad() + ofs) % 9; });
}

}  // namespace tifa_libs::geo

#endif