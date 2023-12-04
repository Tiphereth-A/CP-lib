#ifndef TIFALIBS_COMB_BALL_BOX_IDA
#define TIFALIBS_COMB_BALL_BOX_IDA

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
mint ball_box_ida(u32 ball, u32 box, Binom<mint> const& binom) { return binom.mCn(box + ball - 1, box - 1); }

}  // namespace tifa_libs::math

#endif