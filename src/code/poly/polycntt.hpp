#ifndef TIFALIBS_POLY_SCNTT_FPS
#define TIFALIBS_POLY_SCNTT_FPS

#include "../conv/conv_cntt.hpp"
#include "poly.hpp"

namespace tifa_libs::math {
namespace polycntt_impl_ {
template <class mint, i64 M = -1>
struct cconv_cntt : public CNTT<mint, M> {
  static constexpr auto ct_cat = ct_CNTT;
  constexpr void conv(vec<mint>& l, vec<mint> const& r, u32 sz = 0) { l = conv_cntt(*this, l, r, sz); }
};
}  // namespace polycntt_impl_

template <class mint, i64 M = -1>
using polycntt = poly<mint, polycntt_impl_::cconv_cntt<mint, M>>;

}  // namespace tifa_libs::math

#endif