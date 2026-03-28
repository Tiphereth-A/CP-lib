#pragma once

#include "../../../util/alias/num/lib.hpp"

namespace tifa_libs {

template <class mint>
CEXP mint ball_box_iim(u32 ball, u32 box) NE { return box >= ball; }

}  // namespace tifa_libs
