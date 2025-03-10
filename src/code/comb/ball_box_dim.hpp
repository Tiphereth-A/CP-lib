#ifndef TIFALIBS_COMB_BALL_BOX_DIM
#define TIFALIBS_COMB_BALL_BOX_DIM

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_dim(u32 ball, u32 box) NE { return box >= ball; }

}  // namespace tifa_libs::math

#endif