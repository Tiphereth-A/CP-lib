#ifndef TIFALIBS_MATH_BERLEKAMP_MASSEY
#define TIFALIBS_MATH_BERLEKAMP_MASSEY

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> berlekamp_massey(vec<T> CR a) NE {
  const u32 n = (u32)a.size();
  vec<T> b{1}, c{1};
  b.reserve(n + 1), c.reserve(n + 1);
  T y = 1;
  flt_ (u32, k, 1, n + 1) {
    u32 l = (u32)c.size();
    T x = 0;
    flt_ (u32, i, 0, l) x += c[i] * a[k - l + i];
    b.push_back(0);
    u32 m = (u32)b.size();
    if (x == 0) continue;
    if (const T d_ = x / y; l < m) {
      const auto _ = c;
      c.insert(begin(c), m - l, 0);
      flt_ (u32, i, 0, m) c[m - 1 - i] -= d_ * b[m - 1 - i];
      b = _, y = x;
    } else
      flt_ (u32, i, 0, m) c[l - 1 - i] -= d_ * b[m - 1 - i];
  }
  reverse(c);
  return c;
}

}  // namespace tifa_libs::math

#endif