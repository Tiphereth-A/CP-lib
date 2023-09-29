#ifndef TIFALIBS_POLY_FFT_INFO
#define TIFALIBS_POLY_FFT_INFO

#include "../util/util.hpp"

namespace tifa_libs::math {

struct FFT_INFO {
  static inline vec<size_t> root;

  static void init(size_t n) {
    assert((n & (n - 1)) == 0);
    if (root.size() == n) return;
    root.resize(n);
    for (size_t i = 0; i < n; ++i) root[i] = (root[i >> 1] >> 1) | ((i & 1) * (n >> 1));
  }
};

}  // namespace tifa_libs::math

#endif