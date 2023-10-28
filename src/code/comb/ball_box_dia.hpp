#ifndef TIFA_LIBS_MATH_BALL_BOX_DIA
#define TIFA_LIBS_MATH_BALL_BOX_DIA

#include "stirling2_row_gen.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_dia(u64 ball, u64 box, poly<T> const& s2r) { return std::reduce(s2r.data().begin(), std::next(s2r.data().begin(), (isz)std::min(ball, box) + 1), typename poly<T>::value_type{}); }
template <class T>
constexpr auto ball_box_dia(u64 ball, u64 box) { return ball_box_dia<T>(ball, box, stirling2_row_gen<T>(ball)); }

}  // namespace tifa_libs::math

#endif