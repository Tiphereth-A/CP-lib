#ifndef TIFALIBS_GEO2D_ARGSORT
#define TIFALIBS_GEO2D_ARGSORT

#include "point.hpp"

namespace tifa_libs::geo {

// sort in counterclockwise
template <class FP>
constexpr void argsort(vec<point<FP>> &vp, u32 quad_start = 6) {
  assert(quad_start < 9);
  std::ranges::sort(vp, [ofs = 9 - quad_start](auto const &l, auto const &r) { return l.quad() == r.quad() ? is_pos(l ^ r) : (l.quad() + ofs) % 9 < (r.quad() + ofs) % 9; });
}

}  // namespace tifa_libs::geo

#endif