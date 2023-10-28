#ifndef TIFA_LIBS_MATH_BALL_BOX_DIL
#define TIFA_LIBS_MATH_BALL_BOX_DIL

#include "stirling2_row_gen.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_dil(u64 ball, u64 box, poly<T> const& s2r) { return box < ball ? 0 : s2r[box]; }
template <class T>
constexpr auto ball_box_dil(u64 ball, u64 box) { return ball_box_dil<T>(ball, box, stirling2_row_gen<T>(ball)); }

}  // namespace tifa_libs::math

#endif