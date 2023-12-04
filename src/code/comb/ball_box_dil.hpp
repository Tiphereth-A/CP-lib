#ifndef TIFALIBS_COMB_BALL_BOX_DIL
#define TIFALIBS_COMB_BALL_BOX_DIL

#include "gen_stirling2_row.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_dil(u32 ball, u32 box, poly<T> const& s2r) { return box > ball ? 0 : s2r[box]; }
template <class T>
constexpr auto ball_box_dil(u32 ball, u32 box) { return ball_box_dil<T>(ball, box, gen_stirling2_row<T>(ball)); }

}  // namespace tifa_libs::math

#endif