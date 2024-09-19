#ifndef TIFALIBS_LALG_SHERMAN_MORRISON
#define TIFALIBS_LALG_SHERMAN_MORRISON

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class T = TPN Mat::val_t>
requires std::same_as<T, TPN Mat::val_t>
CEXP void sherman_morrison(Mat &inv_A, vec<T> CR u, vec<T> CR v) {
  const u32 n = inv_A.row();
  assert(n == inv_A.col());
  vec<T> x(n), y(n);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n)
      x[i] += inv_A(i, j) * u[j], y[j] += v[i] * inv_A(i, j);
  T sum = 1;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n) sum += v[i] * inv_A(i, j) * u[j];
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n) inv_A(i, j) -= x[i] * y[j] / sum;
}

}  // namespace tifa_libs::math

#endif