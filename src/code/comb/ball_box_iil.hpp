#ifndef TIFA_LIBS_MATH_BALL_BOX_IIL
#define TIFA_LIBS_MATH_BALL_BOX_IIL

#include "ball_box_ii_gen.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_iil(u64 ball, u64 box, poly<T> const& bbiif) { return ball >= box ? typename T::value_type{0} : bbiif[ball - box]; }
template <class T>
constexpr auto ball_box_iil(u64 ball, u64 box) { return ball_box_iil<T>(ball, box, ball_box_ii_gen<T>(box, ball)); }

}  // namespace tifa_libs::math

#endif