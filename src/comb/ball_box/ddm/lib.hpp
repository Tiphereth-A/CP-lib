#ifndef TIFALIBS_COMB_BALL_BOX_DDM_LIB
#define TIFALIBS_COMB_BALL_BOX_DDM_LIB

#include "../../binom/lib.hpp"

namespace tifa_libs::math {

template <class mint, class fact>
CEXP mint ball_box_ddm(u32 ball, u32 box, binom<mint, fact> CR b) NE { return b.mPn(box, ball); }

}  // namespace tifa_libs::math

#endif