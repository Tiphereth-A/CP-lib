#ifndef TIFALIBS_COMB_BALL_BOX_IDM
#define TIFALIBS_COMB_BALL_BOX_IDM

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_idm(u32 ball, u32 box, Binom<mint> CR binom) { return binom.mCn(box, ball); }

}  // namespace tifa_libs::math

#endif