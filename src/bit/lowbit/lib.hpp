#pragma once

#include "../../util/util/lib.hpp"

namespace tifa_libs {

template <class T>
CEXP T lowbit(T x) NE { return T(1) << std::countr_zero(x); }

}  // namespace tifa_libs
