#pragma once

#include "../../../conv/add/dft/lib.hpp"
#include "../../../conv/trans/ntt/lib.hpp"
#include "../poly_c/lib.hpp"

namespace tifa_libs {
namespace polyntt_impl_ {
template <class mint>
struct cconv_ntt : public ntt<mint> {
  using val_t = mint;
  static CEXP auto ct_cat = CCORE::NTT;
  CEXP void conv(vec<val_t>& l, vec<val_t> CR r, u32 sz = 0) NE { l = conv_dft<cconv_ntt, mint>(*this, l, r, sz); }
};
}  // namespace polyntt_impl_
template <class mint>
using polyntt = poly_impl_::poly<polyntt_impl_::cconv_ntt<mint>>;

}  // namespace tifa_libs
