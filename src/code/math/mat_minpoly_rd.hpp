#ifndef TIFA_LIBS_MATH_MAT_MINPOLY
#define TIFA_LIBS_MATH_MAT_MINPOLY

#include "../util/util.hpp"

#include "lfsr_bm.hpp"

namespace tifa_libs::math {

template <class Mat, class Gn, class Is0, class T = typename Mat::value_type>
inline vec<T> minpoly(Mat const &mat, Gn &gen, Is0 is0) {
  size_t n = mat.row();
  assert(n == mat.col());
  auto gen2 = [&gen](size_t n) {
    vec<T> v(n);
    std::generate(v.begin(), v.end(), gen);
    return v;
  };
  std::vector<T> u = gen2(n), v = gen2(n), _(n * 2);
  for (size_t i = 0; i < n * 2; ++i) {
    _[i] = std::transform_reduce(u.begin(), u.end(), v.begin(), T{});
    v = mat.lproj(v);
  }
  std::vector<T> res = lfsr_bm(_, is0);
  std::reverse(res.begin(), res.end());
  return res;
}

}  // namespace tifa_libs::math

#endif