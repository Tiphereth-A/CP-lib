#ifndef TIFALIBS_LALG_HAFNIAN_MAT
#define TIFALIBS_LALG_HAFNIAN_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat>
CEXP auto hafnian(Mat CR mat) NE {
  using T = TPN Mat::val_t;
  const u32 n = mat.row(), h = n / 2 + 1;
  assert(n == mat.col() && !(n & 1));
  auto add = [&h](vec<T> &x, spn<T> a, spn<T> b) NE {
    flt_ (u32, i, 0, h - 1)
      flt_ (u32, j, 0, h - i - 1) x[i + j + 1] += a[i] * b[j];
  };
  auto f = [&](auto &&f, cT_(v3ec<T>) v) NE -> vec<T> {
    vec<T> ans(h);
    if (v.empty()) {
      ans[0] = 1;
      return ans;
    }
    const u32 m = u32(v.size() - 2);
    auto v_ = v;
    v_.resize(m);
    vec<T> _0 = f(f, v_);
    flt_ (u32, i, 0, m)
      flt_ (u32, j, 0, i) add(v_[i][j], v[m][i], v[m + 1][j]), add(v_[i][j], v[m + 1][i], v[m][j]);
    vec<T> _1 = f(f, v_);
    flt_ (u32, i, 0, h) ans[i] += _1[i] - _0[i];
    add(ans, _1, v[m + 1][m]);
    return ans;
  };
  v3ec<T> v(n);
  flt_ (u32, i, 0, n) {
    v[i].resize(i, vec<T>(h));
    flt_ (u32, j, 0, i) v[i][j][0] = mat(i, j);
  }
  return f(f, v).back();
}

}  // namespace tifa_libs::math

#endif