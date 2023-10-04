#ifndef TIFA_LIBS_GEO2D_TCENTER_EA
#define TIFA_LIBS_GEO2D_TCENTER_EA

#include "triangle.hpp"

namespace tifa_libs::geo2d {

// excenter of A
template <class FP>
constexpr point<FP> center_EA(triangle<FP> const &t) { return t.average_w(-((t.B - t.C).norm()), (t.C - t.A).norm(), (t.A - t.B).norm()); }

}  // namespace tifa_libs::geo2d

#endif
