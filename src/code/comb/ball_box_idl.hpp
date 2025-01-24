#ifndef TIFALIBS_COMB_BALL_BOX_IDL
#define TIFALIBS_COMB_BALL_BOX_IDL

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_idl(u32 ball, u32 box, binom<mint> CR b) NE { return b.mCn(ball - 1, box - 1); }

}  // namespace tifa_libs::math

#endif