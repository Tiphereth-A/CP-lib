#ifndef TIFA_LIBS_GEO2D_POLY_MASSP
#define TIFA_LIBS_GEO2D_POLY_MASSP

#include "polygon.hpp"

namespace tifa_libs::geo {

template <class FP>
point<FP> poly_massp(polygon<FP> const &poly) {
  point<FP> ret{};
  FP area{};
  if (poly.vs.size() == 0) return ret;
  if (poly.vs.size() == 1) return poly.vs[0];
  for (size_t i = 1; i < poly.vs.size() - 1; ++i) {
    FP tmp = cross(poly.vs[0], poly.vs[i], poly.vs[i + 1]);
    if (is_zero(tmp)) continue;
    area += tmp;
    ret += (poly.vs[0] + poly.vs[i] + poly.vs[i + 1]) * (tmp / 3);
  }
  if (!is_zero(area)) ret /= area;
  return ret;
}

}  // namespace tifa_libs::geo

#endif