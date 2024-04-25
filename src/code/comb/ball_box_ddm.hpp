#ifndef TIFALIBS_COMB_BALL_BOX_DDM
#define TIFALIBS_COMB_BALL_BOX_DDM

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_ddm(u32 ball, u32 box, Binom<mint> CR binom) { return binom.mPn(box, ball); }

}  // namespace tifa_libs::math

#endif