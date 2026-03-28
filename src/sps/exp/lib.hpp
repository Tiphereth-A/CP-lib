#pragma once

#include "../../conv/subset/lib.hpp"

namespace tifa_libs {

template <class T, u32 N = 21>
auto exp_fpssps(u32 n, vec<T> g) NE {
  static conv_subset<T, N> ss;
  assert(n <= N && g[0] == 0), g.resize(1 << n);
  vec<T> h{1};
  flt_ (u32, k, 1, n + 1) {
    auto a = ss.conv(h, {begin(g) + (1 << (k - 1)), begin(g) + (1 << k)});
    copy(a, std::back_inserter(h));
  }
  return h;
}

}  // namespace tifa_libs
