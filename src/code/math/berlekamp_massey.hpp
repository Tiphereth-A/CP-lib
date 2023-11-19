#ifndef TIFA_LIBS_MATH_BERLEKAMP_MASSEY
#define TIFA_LIBS_MATH_BERLEKAMP_MASSEY

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
vec<T> berlekamp_massey(vec<T> const &a) {
  u32 n = (u32)a.size();
  vec<T> b{1}, c{1};
  b.reserve(n + 1);
  c.reserve(n + 1);
  T y = 1;
  for (u32 k = 1; k <= n; ++k) {
    u32 l = (u32)c.size();
    T x = 0;
    for (u32 i = 0; i < l; ++i) x += c[i] * a[k - l + i];
    b.push_back(0);
    u32 m = (u32)b.size();
    if (x == 0) continue;
    T d_ = x / y;
    if (l < m) {
      auto _ = c;
      c.insert(c.begin(), m - l, 0);
      for (u32 i = 0; i < m; ++i) c[m - 1 - i] -= d_ * b[m - 1 - i];
      b = _;
      y = x;
    } else
      for (u32 i = 0; i < m; ++i) c[l - 1 - i] -= d_ * b[m - 1 - i];
  }
  std::reverse(c.begin(), c.end());
  return c;
}

}  // namespace tifa_libs::math

#endif