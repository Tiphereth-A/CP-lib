#ifndef TIFALIBS_POLYSPS_EXP
#define TIFALIBS_POLYSPS_EXP

#include "../conv/conv_subset.hpp"

namespace tifa_libs::math {

template <class T, size_t N = 21>
inline vec<T> polysps_exp(size_t n, vec<T> g) {
  assert(n <= N && g[0] == 0);
  static conv_subset<T, N> ss;
  g.resize(1 << n);
  vec<T> h{1};
  for (size_t k = 1; k <= n; ++k) {
    auto a = ss.conv(h, {begin(g) + (1 << (k - 1)), begin(g) + (1 << k)});
    std::copy(begin(a), end(a), std::back_inserter(h));
  }
  return h;
}

}  // namespace tifa_libs::math

#endif