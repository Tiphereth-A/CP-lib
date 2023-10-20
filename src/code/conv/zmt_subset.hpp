#ifndef TIFALIBS_CONV_ZMT_SUBSET
#define TIFALIBS_CONV_ZMT_SUBSET

#include "../bit/ispow2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
void zt_subset(vec<T>& f) {
  usz n = f.size();
  assert(bit::ispow2(n));
  for (usz i = 1; i < n; i *= 2)
    for (usz j = 0; j < n; ++j)
      if (!(j & i)) f[j | i] += f[j];
}

template <class T>
void mt_subset(vec<T>& f) {
  usz n = f.size();
  assert(bit::ispow2(n));
  for (usz i = 1; i < n; i *= 2)
    for (usz j = 0; j < n; ++j)
      if (!(j & i)) f[j | i] -= f[j];
}

}  // namespace tifa_libs::math

#endif