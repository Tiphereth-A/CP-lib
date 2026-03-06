#pragma once

#include "../../../math/qpow/basic/lib.hpp"

namespace tifa_libs::math {

template <class mint>
CEXP mint ball_box_dda(u32 ball, u32 box) NE { return qpow<mint>(box, ball); }

}  // namespace tifa_libs::math
