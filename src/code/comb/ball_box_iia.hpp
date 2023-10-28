#ifndef TIFA_LIBS_MATH_BALL_BOX_IIA
#define TIFA_LIBS_MATH_BALL_BOX_IIA

#include "ball_box_ii_gen.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_iia(u64 ball, u64, poly<T> const& bbiif) { return bbiif[ball]; }
template <class T>
constexpr auto ball_box_iia(u64 ball, u64 box) { return ball_box_iia<T>(ball, box, ball_box_ii_gen<T>(box, ball)); }

}  // namespace tifa_libs::math

#endif