#ifndef TIFA_LIBS_MATH_BALL_BOX_IDL
#define TIFA_LIBS_MATH_BALL_BOX_IDL

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
inline mint ball_box_idl(u64 ball, u64 box, Binom const& binom) { return binom.mCn(ball - 1, box - 1); }

}  // namespace tifa_libs::math

#endif