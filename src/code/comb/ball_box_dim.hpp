#ifndef TIFALIBS_COMB_BALL_BOX_DIM
#define TIFALIBS_COMB_BALL_BOX_DIM

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
constexpr mint ball_box_dim(u32 ball, u32 box) { return box >= ball; }

}  // namespace tifa_libs::math

#endif