#ifndef TIFALIBS_COMB_BALL_BOX_DIA
#define TIFALIBS_COMB_BALL_BOX_DIA

#include "gen_stirling2_row.hpp"

namespace tifa_libs::math {

template <class poly>
CEXP auto ball_box_dia(u32 ball, u32 box, cT_(poly) s2r) { return std::reduce(s2r.data().begin(), s2r.data().begin() + (min(ball, box) + 1), TPN poly::value_type{}); }
template <class poly>
CEXP auto ball_box_dia(u32 ball, u32 box) { return ball_box_dia<poly>(ball, box, gen_stirling2_row<poly>(ball)); }

}  // namespace tifa_libs::math

#endif