#pragma once

#include "../../seq/stirling2_row/lib.hpp"

namespace tifa_libs {

template <class poly>
CEXP TPN poly::val_t ball_box_dil(u32 ball, u32 box, poly CR s2r) NE { retif_((box > ball), 0, s2r[box]); }
template <class poly>
CEXP auto ball_box_dil(u32 ball, u32 box) NE { return ball_box_dil<poly>(ball, box, gen_stirling2_row<poly>(ball)); }

}  // namespace tifa_libs
