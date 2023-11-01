#ifndef TIFA_LIBS_MATH_BALL_BOX_IIA
#define TIFA_LIBS_MATH_BALL_BOX_IIA

#include "gen_ball_box_ii.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_iia(u32 ball, u32, poly<T> const& bbiif) { return bbiif[ball]; }
template <class T>
constexpr auto ball_box_iia(u32 ball, u32 box) { return ball_box_iia<T>(ball, box, gen_ball_box_ii<T>(box, ball)); }

}  // namespace tifa_libs::math

#endif