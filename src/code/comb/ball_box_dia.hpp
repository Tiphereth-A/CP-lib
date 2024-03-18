#ifndef TIFALIBS_COMB_BALL_BOX_DIA
#define TIFALIBS_COMB_BALL_BOX_DIA

#include "gen_stirling2_row.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr auto ball_box_dia(u32 ball, u32 box, poly const& s2r) { return std::reduce(s2r.data().begin(), s2r.data().begin() + (std::min(ball, box) + 1), typename poly::value_type{}); }
template <class poly>
constexpr auto ball_box_dia(u32 ball, u32 box) { return ball_box_dia<poly>(ball, box, gen_stirling2_row<poly>(ball)); }

}  // namespace tifa_libs::math

#endif