#ifndef TIFALIBS_LALG_DET_RD_MAT
#define TIFALIBS_LALG_DET_RD_MAT

#include "lfsr_bm.hpp"

namespace tifa_libs::math {

// OK for matsp
template <class Mat, class Gn, class Is0>
requires requires(Is0 is0, TPN Mat::val_t t) {
  { is0(t) } -> std::same_as<bool>;
}
auto det_rd(Mat mat, Gn& gen, Is0&& is0) NE {
  using T = TPN Mat::val_t;
  const u32 n = mat.row();
  assert(n == mat.col());
  auto gen2 = [&gen](u32 n) NE {
    vec<T> v(n);
    generate(v, gen);
    return v;
  };
  vec<T> u = gen2(n), v = gen2(n), diag = gen2(n), _(n * 2);
  flt_ (u32, i, 0, n * 2) {
    _[i] = std::transform_reduce(begin(u), end(u), begin(v), T{});
    flt_ (u32, i, 0, n) v[i] *= diag[i];
    v = mat.lproj(v);
  }
  T res = lfsr_bm(_, std::forward<Is0>(is0)).back() / std::reduce(begin(diag), end(diag), T(1), std::multiplies<T>());
  retif_(((n & 1) == 1), -res, res);
}

}  // namespace tifa_libs::math

#endif