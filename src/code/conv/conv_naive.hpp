#ifndef TIFALIBS_CONV_CONV_NAIVE
#define TIFALIBS_CONV_CONV_NAIVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class U, class T = U>
inline vec<T> conv_naive(vec<U> const &l, vec<U> const &r, usz ans_size) {
  static_assert(sizeof(U) <= sizeof(T));
  usz n = l.size(), m = r.size();
  vec<T> ans(ans_size);
  if (n < m)
    for (usz j = 0; j < m; ++j)
      for (usz i = 0; i < n; ++i) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  else
    for (usz i = 0; i < n; ++i)
      for (usz j = 0; j < m; ++j) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  return ans;
}
template <class U, class T = U>
inline vec<T> conv_naive(vec<U> const &l, vec<U> const &r) { return conv_naive<U, T>(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif