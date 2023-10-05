#ifndef TIFA_LIBS_GEO2D_ARGSORT_COUNTERCLOCKWISE
#define TIFA_LIBS_GEO2D_ARGSORT_COUNTERCLOCKWISE

#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
inline void argsort_counterclockwise(vec<point<FP>> &vp) {
  std::sort(vp.begin(), vp.end(), [](auto const &l, auto const &r) { return l.quad() == r.quad() ? is_pos(l ^ r) : l.quad() < r.quad(); });
}

}  // namespace tifa_libs::geo

#endif