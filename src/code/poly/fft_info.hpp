#ifndef TIFALIBS_POLY_FFT_INFO
#define TIFALIBS_POLY_FFT_INFO

#include "../util/util.hpp"

namespace tifa_libs::math {

struct FFT_INFO {
  vec<size_t> root;

  FFT_INFO() {}

  void set(size_t n) {
    assert((n & (n - 1)) == 0);
    if (root.size() == n) return;
    root.resize(n);
    for (size_t i = 0; i < n; ++i) root[i] = (root[i / 2] / 2) | ((i & 1) * (n / 2));
  }
};

}  // namespace tifa_libs::math

#endif