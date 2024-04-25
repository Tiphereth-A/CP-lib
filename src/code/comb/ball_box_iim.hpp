#ifndef TIFALIBS_COMB_BALL_BOX_IIM
#define TIFALIBS_COMB_BALL_BOX_IIM

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_iim(u32 ball, u32 box) { return box >= ball; }

}  // namespace tifa_libs::math

#endif