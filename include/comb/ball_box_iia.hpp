#ifndef TIFALIBS_COMB_BALL_BOX_IIA
#define TIFALIBS_COMB_BALL_BOX_IIA

#include "gen_ball_box_ii.hpp"

namespace tifa_libs::math {

template <class poly>
CEXP auto ball_box_iia(u32 ball, u32, poly CR bbiif) NE { return bbiif[ball]; }
template <class poly>
CEXP auto ball_box_iia(u32 ball, u32 box) NE { return ball_box_iia<poly>(ball, box, gen_ball_box_ii<poly>(box, ball)); }

}  // namespace tifa_libs::math

#endif