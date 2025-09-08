#ifndef TIFALIBS_GEO2D_REL_CC
#define TIFALIBS_GEO2D_REL_CC

#include "circle.hpp"
#include "distp_pp.hpp"

namespace tifa_libs::geo {

// relation between circle and circle
// clang-format off
enum class RELCC : u8 { lyingin, touchin, intersect, touchex, lyingout };
// clang-format on

template <class FP>
CEXP RELCC relation_CC(circle<FP> CR c1, circle<FP> CR c2) NE {
  if (const auto d1 = comp_distp(c1.o, c2.o, c1.r + c2.r); d1 > 0) return RELCC::lyingout;
  else if (d1 == 0) return RELCC::touchex;
  if (const auto d2 = comp_distp(c1.o, c2.o, abs(c1.r - c2.r)); d2 > 0) return RELCC::intersect;
  else if (d2 == 0) return RELCC::touchin;
  return RELCC::lyingin;
}

}  // namespace tifa_libs::geo

#endif