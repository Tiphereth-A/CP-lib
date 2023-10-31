#ifndef TIFA_LIBS_MATH_BALL_BOX_DDM
#define TIFA_LIBS_MATH_BALL_BOX_DDM

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
inline mint ball_box_ddm(u64 ball, u64 box, Binom<mint> const& binom) { return binom.mPn(box, ball); }

}  // namespace tifa_libs::math

#endif