#ifndef TIFALIBS_MATRIX_MAT_MINPOLY_RD
#define TIFALIBS_MATRIX_MAT_MINPOLY_RD

#include "lfsr_bm.hpp"

namespace tifa_libs::math {

template <class Mat, class Gn, class Is0, class T = typename Mat::value_type>
vec<T> minpoly(Mat const &mat, Gn &gen, Is0 is0) {
  u32 n = mat.row();
  assert(n == mat.col());
  auto gen2 = [&gen](u32 n) {
    vec<T> v(n);
    std::generate(v.begin(), v.end(), gen);
    return v;
  };
  std::vector<T> u = gen2(n), v = gen2(n), _(n * 2);
  for (u32 i = 0; i < n * 2; ++i) {
    _[i] = std::transform_reduce(u.begin(), u.end(), v.begin(), T{});
    v = mat.lproj(v);
  }
  std::vector<T> res = lfsr_bm(_, is0);
  std::reverse(res.begin(), res.end());
  return res;
}

}  // namespace tifa_libs::math

#endif