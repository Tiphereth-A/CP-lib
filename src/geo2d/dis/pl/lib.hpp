#pragma once

#include "../../proj/lib.hpp"

namespace tifa_libs {

// min dist_PP from a point to a line
template <class FP>
CEXP FP dist_PL(point<FP> CR p, line<FP> CR s) NE { retif_((s.l == s.r), dist_PP(s.l, p), dist_PP(p, proj(s, p))); }

}  // namespace tifa_libs
