#ifndef TIFA_LIBS_GEO2D_TCENTER_H
#define TIFA_LIBS_GEO2D_TCENTER_H

#include "line.hpp"
#include "triangle.hpp"

namespace tifa_libs::geo2d {

// orthocenter (X4)
template <class FP>
constexpr point<FP> center_H(triangle<FP> const &t) { return ins_LL({t.A, t.A + (t.B - t.C).do_rot90()}, {t.B, t.B + (t.C - t.A).do_rot90()}); }

}  // namespace tifa_libs::geo2d

#endif
