#ifndef TIFALIBS_LALG_DET_RD_MAT
#define TIFALIBS_LALG_DET_RD_MAT

#include "lfsr_bm.hpp"

namespace tifa_libs::math {

// OK for matsp
template <class Mat, class Gn, class Is0>
requires requires(Is0 is0, typename Mat::value_type t) {
  { is0(t) } -> std::same_as<bool>;
}
auto det_rd(Mat mat, Gn &gen, Is0 &&is0) {
  using T = typename Mat::value_type;
  u32 n = mat.row();
  assert(n == mat.col());
  auto gen2 = [&gen](u32 n) {
    vec<T> v(n);
    std::generate(v.begin(), v.end(), gen);
    return v;
  };
  vec<T> u = gen2(n), v = gen2(n), diag = gen2(n), _(n * 2);
  for (u32 i = 0; i < n * 2; ++i) {
    _[i] = std::transform_reduce(u.begin(), u.end(), v.begin(), T{});
    for (u32 i = 0; i < n; ++i) v[i] *= diag[i];
    v = mat.lproj(v);
  }
  vec<T> mp = lfsr_bm(_, std::forward<Is0>(is0));
  T res = mp.back() / std::accumulate(diag.begin(), diag.end(), T(1), std::multiplies<T>());
  return (n & 1) == 1 ? -res : res;
}

}  // namespace tifa_libs::math

#endif