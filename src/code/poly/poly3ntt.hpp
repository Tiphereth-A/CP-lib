#ifndef TIFALIBS_POLY_POLY3NTT
#define TIFALIBS_POLY_POLY3NTT

#include "../conv/conv_3ntt.hpp"
#include "poly.hpp"

namespace tifa_libs::math {
namespace poly3ntt_impl_ {
template <class mint0, class mint1, class mint2>
struct cconv_3ntt {
  std::tuple<NTT<mint0>, NTT<mint1>, NTT<mint2>> ccore;
  static CEXP auto ct_cat = ct_3NTT;
  template <class mint>
  CEXP void conv(vec<mint> &l, vec<mint> CR r, u32 sz = 0) { l = conv_3ntt<mint, mint0, mint1, mint2>(ccore, l, r, sz); }
};
}  // namespace poly3ntt_impl_

template <class mint, class mint0, class mint1, class mint2>
using poly3ntt = poly<mint, poly3ntt_impl_::cconv_3ntt<mint0, mint1, mint2>>;

}  // namespace tifa_libs::math

#endif