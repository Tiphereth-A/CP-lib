#ifndef TIFALIBS_FPS_DS_NTT_LIB
#define TIFALIBS_FPS_DS_NTT_LIB

#include "../../../conv/add/dft/lib.hpp"
#include "../../../conv/trans/ntt/lib.hpp"
#include "../poly/lib.hpp"

namespace tifa_libs::math {
namespace polyntt_impl_ {
template <class mint>
struct cconv_ntt : public ntt<mint> {
  static CEXP auto ct_cat = CCORE::NTT;
  CEXP void conv(vec<mint>& l, vec<mint> CR r, u32 sz = 0) NE { l = conv_dft<cconv_ntt, mint>(*this, l, r, sz); }
};
}  // namespace polyntt_impl_

template <class mint>
using polyntt = poly<polyntt_impl_::cconv_ntt, mint>;

}  // namespace tifa_libs::math

#endif