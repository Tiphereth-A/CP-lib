#ifndef TIFALIBS_COMB_BALL_BOX_IIA
#define TIFALIBS_COMB_BALL_BOX_IIA

#include "gen_ball_box_ii.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr auto ball_box_iia(u32 ball, u32, poly const& bbiif) { return bbiif[ball]; }
template <class poly>
constexpr auto ball_box_iia(u32 ball, u32 box) { return ball_box_iia<poly>(ball, box, gen_ball_box_ii<poly>(box, ball)); }

}  // namespace tifa_libs::math

#endif