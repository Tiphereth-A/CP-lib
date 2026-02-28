#ifndef TIFALIBS_COMB_BALL_BOX_IIM_LIB
#define TIFALIBS_COMB_BALL_BOX_IIM_LIB

#include "../../../util/alias/num/lib.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_iim(u32 ball, u32 box) NE { return box >= ball; }

}  // namespace tifa_libs::math

#endif