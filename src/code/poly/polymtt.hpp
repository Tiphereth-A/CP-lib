#ifndef TIFALIBS_POLY_POLYMTT
#define TIFALIBS_POLY_POLYMTT

#include "../conv/conv_mtt.hpp"
#include "poly.hpp"

namespace tifa_libs::math {
namespace polymtt_impl_ {
template <class mint, class FP>
struct cconv_mtt : public FFT<FP> {
  static CEXP auto ct_cat = ct_FFT;
  CEXP void conv(vec<mint>& l, vec<mint> CR r, u32 sz = 0) NE { l = conv_mtt(*this, l, r, sz); }
};
}  // namespace polymtt_impl_

template <class mint, class FP = f64>
using polymtt = poly<polymtt_impl_::cconv_mtt, mint, FP>;

}  // namespace tifa_libs::math

#endif