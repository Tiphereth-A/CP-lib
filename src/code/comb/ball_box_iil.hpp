#ifndef TIFALIBS_COMB_BALL_BOX_IIL
#define TIFALIBS_COMB_BALL_BOX_IIL

#include "gen_ball_box_ii.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_iil(u32 ball, u32 box, poly<T> const& bbiif) { return ball >= box ? bbiif[ball - box] : typename T::value_type{0}; }
template <class T>
constexpr auto ball_box_iil(u32 ball, u32 box) { return ball_box_iil<T>(ball, box, gen_ball_box_ii<T>(box, ball)); }

}  // namespace tifa_libs::math

#endif