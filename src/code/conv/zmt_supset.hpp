#ifndef TIFALIBS_CONV_ZMT_SUPSET
#define TIFALIBS_CONV_ZMT_SUPSET

#include "../bit/ispow2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
void zt_supset(vec<T>& f) {
  u32 n = (u32)f.size();
  assert(bit::ispow2(n));
  for (u32 i = 1; i < n; i *= 2)
    for (u32 j = 0; j < n; ++j)
      if (!(j & i)) f[j] += f[j | i];
}
template <class T>
void mt_supset(vec<T>& f) {
  u32 n = (u32)f.size();
  assert(bit::ispow2(n));
  for (u32 i = 1; i < n; i *= 2)
    for (u32 j = 0; j < n; ++j)
      if (!(j & i)) f[j] -= f[j | i];
}

}  // namespace tifa_libs::math

#endif