#ifndef TIFALIBS_CONV_ZMT_SUBSET
#define TIFALIBS_CONV_ZMT_SUBSET

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
CEXP void zt_subset(vec<T>& f) {
  u32 n = (u32)f.size();
  assert(std::has_single_bit(n));
  for (u32 i = 1; i < n; i *= 2)
    flt_ (u32, j, 0, n)
      if (!(j & i)) f[j | i] += f[j];
}
template <class T>
CEXP void mt_subset(vec<T>& f) {
  u32 n = (u32)f.size();
  assert(std::has_single_bit(n));
  for (u32 i = 1; i < n; i *= 2)
    flt_ (u32, j, 0, n)
      if (!(j & i)) f[j | i] -= f[j];
}

}  // namespace tifa_libs::math

#endif