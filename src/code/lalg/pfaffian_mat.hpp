#ifndef TIFALIBS_LALG_PFAFFIAN_MAT
#define TIFALIBS_LALG_PFAFFIAN_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0>
requires requires(Is0 is0, TPN Mat::value_type t) {
  { is0(t) } -> std::same_as<bool>;
}
CEXP auto pfaffian(Mat mat, Is0 is0) {
  using T = TPN Mat::value_type;
  const u32 n = mat.row();
  assert(n == mat.col() && !(n & 1));
  bool neg = 0;
  for (u32 i = 0; i < n; i += 2) {
    u32 p = i + 1;
    flt_ (u32, j, i + 2, n)
      if (!is0(mat(i, j))) {
        p = j;
        break;
      }
    if (p != i + 1) {
      neg ^= 1;
      fle_ (u32, j, 0, i) swap(mat(j, i + 1), mat(j, p));
      flt_ (u32, j, i + 2, p) swap(mat(i + 1, j), mat(j, p)), mat(i + 1, j) = -mat(i + 1, j), mat(j, p) = -mat(j, p);
      mat(i + 1, p) = -mat(i + 1, p);
      flt_ (u32, j, p + 1, n) swap(mat(i + 1, j), mat(p, j));
    }
    T _ = mat(i, i + 1).inv();
    flt_ (u32, j, i + 2, n)
      if (mat(i, j)) {
        T _2 = -mat(i, j) * _;
        fle_ (u32, k, 0, i) mat(k, j) += _2 * mat(k, i + 1);
        flt_ (u32, k, i + 2, j) mat(k, j) -= _2 * mat(i + 1, k);
        flt_ (u32, k, j + 1, n) mat(j, k) += _2 * mat(i + 1, k);
      }
  }
  T ans = 1;
  for (u32 i = 0; i < n; i += 2) ans *= mat(i, i + 1);
  return neg ? -ans : ans;
}

}  // namespace tifa_libs::math

#endif