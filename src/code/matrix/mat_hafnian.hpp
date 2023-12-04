#ifndef TIFALIBS_MATRIX_MAT_HAFNIAN
#define TIFALIBS_MATRIX_MAT_HAFNIAN

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class T = typename Mat::value_type>
T hafnian(Mat const &mat) {
  u32 n = mat.row(), h = n / 2 + 1;
  assert(n == mat.col() && !(n & 1));

  auto add = [&h](vec<T> &x, vec<T> const &a, vec<T> const &b) {
    for (u32 i = 0; i < h - 1; ++i)
      for (u32 j = 0; j < h - 1 - i; ++j) x[i + j + 1] += a[i] * b[j];
  };
  auto solve = [&](auto &&f, vvvec<T> const &v) -> vec<T> {
    vec<T> ans(h);
    if (v.empty()) {
      ans[0] = 1;
      return ans;
    }
    u32 m = u32(v.size() - 2);
    auto v_ = v;
    v_.resize(m);
    vec<T> _0 = f(f, v_);
    for (u32 i = 0; i < m; ++i)
      for (u32 j = 0; j < i; ++j) {
        add(v_[i][j], v[m][i], v[m + 1][j]);
        add(v_[i][j], v[m + 1][i], v[m][j]);
      }
    vec<T> _1 = f(f, v_);
    for (u32 i = 0; i < h; ++i) ans[i] += _1[i] - _0[i];
    add(ans, _1, v[m + 1][m]);
    return ans;
  };

  vvvec<T> v(n);
  for (u32 i = 0; i < n; ++i) {
    v[i].resize(i, vec<T>(h));
    for (u32 j = 0; j < i; ++j) v[i][j][0] = mat(i, j);
  }
  return solve(solve, v).back();
}

}  // namespace tifa_libs::math

#endif