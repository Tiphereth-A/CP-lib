#pragma once

#include "../../ds/pl/lib.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP sdist3_PlP(planev<FP> pl, point3d<FP> CR p) NE { return (p - *pl.u) * pl.normal() / pl.normal().norm(); }

}  // namespace tifa_libs::geo
