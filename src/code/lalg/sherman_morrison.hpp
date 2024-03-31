#ifndef TIFALIBS_LALG_SHERMAN_MORRISON
#define TIFALIBS_LALG_SHERMAN_MORRISON

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class T = typename Mat::value_type>
requires std::same_as<T, typename Mat::value_type>
constexpr void sherman_morrison(Mat &inv_A, vec<T> const &u, vec<T> const &v) {
  u32 n = inv_A.row();
  assert(n == inv_A.col());
  vec<T> x(n), y(n);
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j < n; ++j)
      x[i] += inv_A(i, j) * u[j], y[j] += v[i] * inv_A(i, j);
  T sum = 1;
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j < n; ++j) sum += v[i] * inv_A(i, j) * u[j];
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j < n; ++j) inv_A(i, j) -= x[i] * y[j] / sum;
}

}  // namespace tifa_libs::math

#endif