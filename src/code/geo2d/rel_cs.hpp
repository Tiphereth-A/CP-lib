#ifndef TIFA_LIBS_GEO2D_REL_CS
#define TIFA_LIBS_GEO2D_REL_CS

#include "circle.hpp"
#include "line.hpp"

namespace tifa_libs::geo2d {

// relation between circle and segment/line
enum RELCS {
  otherwise_cs,
  tagante_cs,
  intersect_cs,
};

template <class FP>
constexpr RELCS relation_CS(circle<FP> const &c, line<FP> const &s) {
  FP d = dist_PL(c.o, s);
  if (is_le(d, c.r)) return RELCS::intersect_cs;
  if (is_eq(d, c.r)) return RELCS::tagante_cs;
  return RELCS::otherwise_cs;
}

}  // namespace tifa_libs::geo2d

#endif