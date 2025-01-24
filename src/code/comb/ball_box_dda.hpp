#ifndef TIFALIBS_COMB_BALL_BOX_DDA
#define TIFALIBS_COMB_BALL_BOX_DDA

#include "../math/qpow.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_dda(u32 ball, u32 box) NE { return qpow<mint>(box, ball); }

}  // namespace tifa_libs::math

#endif