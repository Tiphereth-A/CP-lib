#ifndef TIFA_LIBS_GEO2D_INV_C2L
#define TIFA_LIBS_GEO2D_INV_C2L

#include "inv_p2p.hpp"

namespace tifa_libs::geo2d {

// geometry inverse of a circle which pass through the inversion center
template <class FP>
constexpr line<FP> inv_C2L(circle<FP> const &c, circle<FP> const &c2) {
  point v = (c2.o - c.o).do_rot90();
  return {inv_P2P(c, c2.o + v), inv_P2P(c, c2.o - v)};
}

}  // namespace tifa_libs::geo2d

#endif