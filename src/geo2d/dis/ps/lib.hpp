#pragma once

#include "../../dis/pp_p/lib.hpp"
#include "../../pred/is_in_middle_p/lib.hpp"
#include "../../proj/lib.hpp"

namespace tifa_libs::geo {

// the point which is min dist_PP from a point to another point which belongs to a segment
template <class FP>
CEXP point<FP> dist_PS_P(point<FP> CR p, line<FP> CR s) NE {
  if (s.l == s.r) return s.l;
  if (const point<FP> h = proj(s, p); is_in_middle(s.l, h, s.r)) return h;
  retif_((comp_distp(s.l, p, s.r, p) < 0), s.l, s.r);
}
// min dist_PP from a point to another point which belongs to a segment
template <class FP>
CEXP FP dist_PS(point<FP> CR p, line<FP> CR s) NE { return dist_PP(dist_PS_P(p, s), p); }

}  // namespace tifa_libs::geo
