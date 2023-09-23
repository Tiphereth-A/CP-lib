#ifndef TIFA_LIBS_GEO2D_POLYGON
#define TIFA_LIBS_GEO2D_POLYGON

#include "polygon_class.hpp"
#include "util.hpp"

#include "circle.hpp"

namespace tifa_libs::geo2d {
data_t area_PoC(const Polygon &poly, const Circle &c) {
  data_t ans{};
  size_t sz = poly.vs.size();
  if (sz < 3) return ans;
  for (size_t i = 0; i < sz; ++i) ans += sarea_CT(c, poly[i], poly[poly.next(i)]);
  return std::abs(ans);
}
}  // namespace tifa_libs::geo2d

#endif