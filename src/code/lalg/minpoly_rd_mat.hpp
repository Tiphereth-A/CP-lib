#ifndef TIFALIBS_LALG_MINPOLY_RD_MAT
#define TIFALIBS_LALG_MINPOLY_RD_MAT

#include "lfsr_bm.hpp"

namespace tifa_libs::math {

template <class Mat, class Gn, class Is0>
requires requires(Is0 is0, typename Mat::value_type t) {
  { is0(t) } -> std::same_as<bool>;
}
auto minpoly(Mat const &mat, Gn &gen, Is0 &&is0) {
  using T = typename Mat::value_type;
  u32 n = mat.row();
  assert(n == mat.col());
  auto gen2 = [&gen](u32 n) {
    vec<T> v(n);
    std::ranges::generate(v, gen);
    return v;
  };
  vec<T> u = gen2(n), v = gen2(n), _(n * 2);
  for (u32 i = 0; i < n * 2; ++i) {
    _[i] = std::transform_reduce(u.begin(), u.end(), v.begin(), T{});
    v = mat.lproj(v);
  }
  vec<T> res = lfsr_bm(_, std::forward<Is0>(is0));
  std::ranges::reverse(res);
  return res;
}

}  // namespace tifa_libs::math

#endif