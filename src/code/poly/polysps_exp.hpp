#ifndef TIFALIBS_POLY_POLYSPS_EXP
#define TIFALIBS_POLY_POLYSPS_EXP

#include "../conv/conv_subset.hpp"

namespace tifa_libs::math {

template <class T, u32 N = 21>
vec<T> polysps_exp(u32 n, vec<T> g) {
  assert(n <= N && g[0] == 0);
  static conv_subset<T, N> ss;
  g.resize(1 << n);
  vec<T> h{1};
  for (u32 k = 1; k <= n; ++k) {
    auto a = ss.conv(h, {begin(g) + (1 << (k - 1)), begin(g) + (1 << k)});
    std::copy(begin(a), end(a), std::back_inserter(h));
  }
  return h;
}

}  // namespace tifa_libs::math

#endif