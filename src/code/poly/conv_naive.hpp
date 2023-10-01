#ifndef TIFALIBS_POLY_CONV_NAIVE
#define TIFALIBS_POLY_CONV_NAIVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
inline vec<T> conv_naive(vec<T> const &l, vec<T> const &r, size_t ans_size) {
  size_t n = l.size(), m = r.size();
  vec<T> ans(ans_size);
  if (n < m)
    for (size_t j = 0; j < m; ++j)
      for (size_t i = 0; i < n; ++i) {
        if (i + j >= ans_size) break;
        ans[i + j] += l[i] * r[j];
      }
  else
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < m; ++j) {
        if (i + j >= ans_size) break;
        ans[i + j] += l[i] * r[j];
      }
  return ans;
}
template <class T>
inline vec<T> conv_naive(vec<T> const &l, vec<T> const &r) { return conv_naive(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif