#ifndef TIFALIBS_POLY_POLYMTT
#define TIFALIBS_POLY_POLYMTT

#include "../conv/conv_mtt.hpp"
#include "poly.hpp"

namespace tifa_libs::math {
namespace polymtt_impl_ {
template <class FP = f64>
struct cconv_mtt : public FFT<FP> {
  static constexpr auto ct_cat = ct_FFT;
  template <class mint>
  constexpr void conv(vec<mint>& l, vec<mint> const& r, u32 sz = 0) { l = conv_mtt(*this, l, r, sz); }
};
}  // namespace polymtt_impl_

template <class mint, class FP = f64>
using polymtt = poly<mint, polymtt_impl_::cconv_mtt<FP>>;

}  // namespace tifa_libs::math

#endif