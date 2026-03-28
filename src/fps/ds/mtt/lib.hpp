#pragma once

#include "../../../conv/add/mtt/lib.hpp"
#include "../poly_c/lib.hpp"

namespace tifa_libs {
namespace polymtt_impl_ {
template <class mint, class FP>
struct cconv_mtt : public fft_r2<FP> {
  using val_t = mint;
  static CEXP auto ct_cat = CCORE::FFT_R2;
  CEXP void conv(vec<val_t>& l, vec<val_t> CR r, u32 sz = 0) NE { l = conv_mtt(*this, l, r, sz); }
};
}  // namespace polymtt_impl_
template <class mint, class FP = f64>
using polymtt = poly_impl_::poly<polymtt_impl_::cconv_mtt<mint, FP>>;

}  // namespace tifa_libs
