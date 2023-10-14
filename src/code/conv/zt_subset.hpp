#ifndef TIFALIBS_CONV_ZT_SUBSET
#define TIFALIBS_CONV_ZT_SUBSET

#include "../bit/ispow2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
void zt_subset(vec<T>& f) {
  size_t n = f.size();
  assert(bit::ispow2(n));
  for (size_t i = 1; i < n; i *= 2)
    for (size_t j = 0; j < n; ++j)
      if (!(j & i)) f[j | i] += f[j];
}

}  // namespace tifa_libs::math

#endif