#ifndef TIFALIBS_COMB_BALL_BOX_IIL
#define TIFALIBS_COMB_BALL_BOX_IIL

#include "gen_ball_box_ii.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr auto ball_box_iil(u32 ball, u32 box, poly const& bbiif) { return ball >= box ? bbiif[ball - box] : typename poly::value_type{0}; }
template <class poly>
constexpr auto ball_box_iil(u32 ball, u32 box) { return ball_box_iil<poly>(ball, box, gen_ball_box_ii<poly>(box, ball)); }

}  // namespace tifa_libs::math

#endif