#ifndef TIFALIBS_COMB_BALL_BOX_DIL
#define TIFALIBS_COMB_BALL_BOX_DIL

#include "gen_stirling2_row.hpp"

namespace tifa_libs::math {

template <class poly>
CEXP auto ball_box_dil(u32 ball, u32 box, poly CR s2r) { return box > ball ? 0 : s2r[box]; }
template <class poly>
CEXP auto ball_box_dil(u32 ball, u32 box) { return ball_box_dil<poly>(ball, box, gen_stirling2_row<poly>(ball)); }

}  // namespace tifa_libs::math

#endif