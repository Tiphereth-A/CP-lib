#pragma once

#include "../../binom/lib.hpp"

namespace tifa_libs::math {

template <class mint, class fact>
CEXP mint ball_box_ddm(u32 ball, u32 box, binom<mint, fact> CR b) NE { return b.mPn(box, ball); }

}  // namespace tifa_libs::math
