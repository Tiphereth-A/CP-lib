#ifndef TIFALIBS_GEO2D_REL_CS
#define TIFALIBS_GEO2D_REL_CS

#include "circle.hpp"
#include "line.hpp"

namespace tifa_libs::geo {

// relation between circle and segment/line
enum RELCS { otherwise_cs,
             tagante_cs,
             intersect_cs };

template <class FP>
CEXP RELCS relation_CS(circle<FP> CR c, line<FP> CR s) NE {
  const FP d = dist_PL(c.o, s);
  if (is_lt(d, c.r)) return intersect_cs;
  if (is_eq(d, c.r)) return tagante_cs;
  return otherwise_cs;
}

}  // namespace tifa_libs::geo

#endif