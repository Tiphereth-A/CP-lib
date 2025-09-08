#ifndef TIFALIBS_COMB_BALL_BOX_DIA
#define TIFALIBS_COMB_BALL_BOX_DIA

#include "gen_stirling2_row.hpp"

namespace tifa_libs::math {

template <class poly>
CEXP auto ball_box_dia(u32 ball, u32 box, poly CR s2r) NE { return std::reduce(begin(s2r), begin(s2r) + (min(ball, box) + 1), TPN poly::val_t{}); }
template <class poly>
CEXP auto ball_box_dia(u32 ball, u32 box) NE { return ball_box_dia<poly>(ball, box, gen_stirling2_row<poly>(ball)); }

}  // namespace tifa_libs::math

#endif