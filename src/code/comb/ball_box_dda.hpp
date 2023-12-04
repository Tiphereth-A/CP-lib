#ifndef TIFALIBS_COMB_BALL_BOX_DDA
#define TIFALIBS_COMB_BALL_BOX_DDA

#include "../math/qpow.hpp"

namespace tifa_libs::math {

template <class mint>
constexpr mint ball_box_dda(u32 ball, u32 box) { return qpow<mint>(box, ball); }

}  // namespace tifa_libs::math

#endif