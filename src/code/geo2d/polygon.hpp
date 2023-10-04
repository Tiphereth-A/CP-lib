#ifndef TIFA_LIBS_GEO2D_POLYGON
#define TIFA_LIBS_GEO2D_POLYGON

#include "polygon_class.hpp"

#include "circle.hpp"

namespace tifa_libs::geo2d {

template <class FP>
FP area_PoC(polygon<FP> const &poly, circle<FP> const &c) {
  FP ans{};
  size_t sz = poly.vs.size();
  if (sz < 3) return ans;
  for (size_t i = 0; i < sz; ++i) ans += sarea_CT(c, poly[i], poly[poly.next(i)]);
  return std::abs(ans);
}

}  // namespace tifa_libs::geo2d

#endif