#ifndef TIFALIBS_POLY_POLYNTT32
#define TIFALIBS_POLY_POLYNTT32

#include "../conv/conv_dft.hpp"
#include "../conv/ntt32.hpp"
#include "poly.hpp"

namespace tifa_libs::math {

namespace polyntt32_impl_ {
template <class mint>
struct cconv_ntt32 : public NTT32<mint> {
  static constexpr auto ct_cat = ct_NTT;
  constexpr void conv(vec<mint> &l, vec<mint> const &r, u32 sz = 0) { l = conv_dft(*this, l, r, sz); }
};
}  // namespace polyntt32_impl_

template <class mint>
using polyntt32 = poly<mint, polyntt32_impl_::cconv_ntt32<mint>>;

}  // namespace tifa_libs::math

#endif