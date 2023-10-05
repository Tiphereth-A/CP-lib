#ifndef TIFA_LIBS_GEO3D_REL_PLP
#define TIFA_LIBS_GEO3D_REL_PLP

#include "plane.hpp"
#include "point3d.hpp"

namespace tifa_libs::geo {

// relation between plane and point3d
enum RELPLP {
  above_plp,
  in_plp,
  below_plp
};

template <class FP>
constexpr RELPLP relation_PlP(plane<FP> const &pl, point3d<FP> const &p) {
  FP d = (p - pl.u) * pl.normal();
  if (is_pos(d)) return above_plp;
  if (is_neg(d)) return below_plp;
  return in_plp;
}

}  // namespace tifa_libs::geo

#endif