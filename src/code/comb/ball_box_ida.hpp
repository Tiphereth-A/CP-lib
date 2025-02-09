#ifndef TIFALIBS_COMB_BALL_BOX_IDA
#define TIFALIBS_COMB_BALL_BOX_IDA

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint, class fact>
CEXP mint ball_box_ida(u32 ball, u32 box, binom<mint, fact> CR b) NE { return b.mCn(box + ball - 1, box - 1); }

}  // namespace tifa_libs::math

#endif