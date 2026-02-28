#ifndef TIFALIBS_COMB_BALL_BOX_DDA_LIB
#define TIFALIBS_COMB_BALL_BOX_DDA_LIB

#include "../../../math/qpow/basic/lib.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_dda(u32 ball, u32 box) NE { return qpow<mint>(box, ball); }

}  // namespace tifa_libs::math

#endif