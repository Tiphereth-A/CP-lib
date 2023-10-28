#ifndef TIFA_LIBS_MATH_BALL_BOX_DDA
#define TIFA_LIBS_MATH_BALL_BOX_DDA

#include "../math/qpow.hpp"

namespace tifa_libs::math {

template <class mint>
constexpr mint ball_box_dda(u64 ball, u64 box) { return qpow<mint>(box, ball); }

}  // namespace tifa_libs::math

#endif