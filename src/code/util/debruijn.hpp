#ifndef TIFALIBS_UTIL_DEBRUIJN
#define TIFALIBS_UTIL_DEBRUIJN

#include "util.hpp"

namespace tifa_libs::util {

// Given alphabet $[0,k)$ constructs a cyclic string of length $k^n$ that contains every length $n$ string as substr
CEXP vecu deBruijn(u32 n, u32 k, u32 maxsz = 0) {
  if (k == 1) return {0};
  if (!maxsz) {
    maxsz = 1;
    flt_ (u32, i, 0, n) maxsz *= k;
  }
  vecu ret, _(n + 1);
  auto f = [&](auto&& f, u32 t, u32 p) -> void {
    if (ret.size() >= maxsz) return;
    if (t > n) {
      if (!(n % p))
        fle_ (u32, i, 1, p) ret.push_back(_[i]);
      if (ret.size() >= maxsz) return;
    } else {
      _[t] = _[t - p];
      if (ret.size() >= maxsz) return;
      f(f, t + 1, p);
      while (++_[t] < k) {
        if (ret.size() >= maxsz) return;
        f(f, t + 1, t);
      }
    }
  };
  f(f, 1, 1);
  ret.resize(maxsz);
  return ret;
}

}  // namespace tifa_libs::util

#endif