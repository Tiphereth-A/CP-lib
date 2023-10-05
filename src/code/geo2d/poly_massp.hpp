#ifndef TIFA_LIBS_GEO2D_POLY_MASSP
#define TIFA_LIBS_GEO2D_POLY_MASSP

#include "polygon.hpp"

namespace tifa_libs::geo {

template <class FP>
point<FP> poly_massp(polygon<FP> const &po) {
  point<FP> ret{};
  FP area{};
  if (po.vs.size() == 0) return ret;
  if (po.vs.size() == 1) return po.vs[0];
  for (size_t i = 1; i < po.vs.size() - 1; ++i) {
    FP tmp = cross(po.vs[0], po.vs[i], po.vs[i + 1]);
    if (is_zero(tmp)) continue;
    area += tmp;
    ret += (po.vs[0] + po.vs[i] + po.vs[i + 1]) * (tmp / 3);
  }
  if (!is_zero(area)) ret /= area;
  return ret;
}

}  // namespace tifa_libs::geo

#endif