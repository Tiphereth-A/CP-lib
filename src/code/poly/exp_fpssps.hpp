#ifndef TIFALIBS_POLY_EXP_FPSSPS
#define TIFALIBS_POLY_EXP_FPSSPS

#include "../conv/conv_subset.hpp"

namespace tifa_libs::math {

template <class T, u32 N = 21>
auto exp_fpssps(u32 n, vec<T> g) {
  static conv_subset<T, N> ss;
  assert(n <= N && g[0] == 0), g.resize(1 << n);
  vec<T> h{1};
  flt_ (u32, k, 1, n + 1) {
    auto a = ss.conv(h, {begin(g) + (1 << (k - 1)), begin(g) + (1 << k)});
    std::ranges::copy(a, std::back_inserter(h));
  }
  return h;
}

}  // namespace tifa_libs::math

#endif