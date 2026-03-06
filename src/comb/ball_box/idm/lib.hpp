#pragma once

#include "../../binom/lib.hpp"

namespace tifa_libs::math {

template <class mint, class fact>
CEXP mint ball_box_idm(u32 ball, u32 box, binom<mint, fact> CR b) NE { return b.mCn(box, ball); }

}  // namespace tifa_libs::math
