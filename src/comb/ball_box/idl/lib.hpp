#pragma once

#include "../../binom/lib.hpp"

namespace tifa_libs {

template <class mint, class fact>
CEXP mint ball_box_idl(u32 ball, u32 box, binom<mint, fact> CR b) NE { return b.mCn(ball - 1, box - 1); }

}  // namespace tifa_libs
