#ifndef TIFA_LIBS_MATH_BALL_BOX_IDA
#define TIFA_LIBS_MATH_BALL_BOX_IDA

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
inline mint ball_box_ida(u64 ball, u64 box, Binom<mint> const& binom) { return binom.mCn(box + ball - 1, box - 1); }

}  // namespace tifa_libs::math

#endif