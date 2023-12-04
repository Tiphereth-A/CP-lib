#ifndef TIFALIBS_COMB_BALL_BOX_DIA
#define TIFALIBS_COMB_BALL_BOX_DIA

#include "gen_stirling2_row.hpp"

namespace tifa_libs::math {

template <class T>
constexpr auto ball_box_dia(u32 ball, u32 box, poly<T> const& s2r) { return std::reduce(s2r.data().begin(), std::next(s2r.data().begin(), (isz)std::min(ball, box) + 1), typename poly<T>::value_type{}); }
template <class T>
constexpr auto ball_box_dia(u32 ball, u32 box) { return ball_box_dia<T>(ball, box, gen_stirling2_row<T>(ball)); }

}  // namespace tifa_libs::math

#endif