#ifndef TIFALIBS_COMB_BALL_BOX_IIL
#define TIFALIBS_COMB_BALL_BOX_IIL

#include "gen_ball_box_ii.hpp"

namespace tifa_libs::math {

template <class poly>
CEXP auto ball_box_iil(u32 ball, u32 box, poly CR bbiif) NE { retif_((ball >= box), bbiif[ball - box], TPN poly::val_t{0}); }
template <class poly>
CEXP auto ball_box_iil(u32 ball, u32 box) NE { return ball_box_iil<poly>(ball, box, gen_ball_box_ii<poly>(box, ball)); }

}  // namespace tifa_libs::math

#endif