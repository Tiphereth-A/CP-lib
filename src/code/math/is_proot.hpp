#ifndef TIFA_LIBS_MATH_IS_PROOT
#define TIFA_LIBS_MATH_IS_PROOT

#include "qpow_mod.hpp"

namespace tifa_libs::math {

template <class T, class It>
constexpr bool is_proot(T g, T m, It pf_begin, It pf_end) {
  static_assert(std::is_unsigned_v<T>);
  if (!g) return false;
  for (; pf_begin != pf_end; ++pf_begin)
    if (qpow_mod(g, (m - 1) / *pf_begin, m) == 1) return false;
  return true;
}

}  // namespace tifa_libs::math

#endif