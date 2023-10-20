#ifndef TIFA_LIBS_MATH_LFSR_BM
#define TIFA_LIBS_MATH_LFSR_BM

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, class Is0>
inline vec<T> lfsr_bm(vec<T> const &s, Is0 is0) {
  vec<T> C{1}, B(C);
  T b(1);
  for (usz n = 0, n_ed = s.size(), l = 0, x = 1; n < n_ed; ++n) {
    T d(s[n]);
    for (usz i = 1; i <= l; ++i) d += C[i] * s[n - i];
    if (is0(d)) ++x;
    else if (l * 2 > n) {
      if (C.size() < B.size() + x) C.resize(B.size() + x);
      T coef = d / b;
      for (usz i = x, ie = B.size() + x; i < ie; ++i) C[i] -= coef * B[i - x];
      ++x;
    } else {
      vec<T> t(C);
      if (C.size() < B.size() + x) C.resize(B.size() + x);
      T _ = d / b;
      for (usz i = x, ie = B.size() + x; i < ie; ++i) C[i] -= _ * B[i - x];
      l = n + 1 - l;
      B = t;
      b = d;
      x = 1;
    }
  }
  return C;
}

}  // namespace tifa_libs::math

#endif