#ifndef TIFA_LIBS_MATH_BALL_BOX_IDM
#define TIFA_LIBS_MATH_BALL_BOX_IDM

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
inline mint ball_box_idm(u64 ball, u64 box, Binom<mint> const& binom) { return binom.mCn(box, ball); }

}  // namespace tifa_libs::math

#endif