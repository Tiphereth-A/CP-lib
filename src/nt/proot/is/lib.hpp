#pragma once

#include "../../../math/qpow/mod/lib.hpp"

namespace tifa_libs {

template <std::unsigned_integral T, class It>
CEXP bool is_proot(T g, T m, It pf_begin, It pf_end) NE {
  retif_((!g) [[unlikely]], false);
  for (; pf_begin != pf_end; ++pf_begin)
    if (qpow_mod(g, (m - 1) / *pf_begin, m) == 1) return false;
  return true;
}

}  // namespace tifa_libs
