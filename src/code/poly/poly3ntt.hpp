#ifndef TIFALIBS_POLY_POLY3NTT
#define TIFALIBS_POLY_POLY3NTT

#include "../conv/conv_3ntt.hpp"
#include "poly.hpp"

namespace tifa_libs::math {
namespace poly3ntt_impl_ {
template <class mint, class mint0, class mint1, class mint2>
struct cconv_3ntt {
  // clang-format off
  struct ntt3 { NTT<mint0> _0; NTT<mint1> _1; NTT<mint2> _2; } ccore;
  // clang-format on
  static CEXP auto ct_cat = ct_3NTT;
  CEXP void conv(vec<mint> &l, vec<mint> CR r, u32 sz = 0) NE { l = conv_3ntt<mint, mint0, mint1, mint2>(ccore._0, ccore._1, ccore._2, l, r, sz); }
};
}  // namespace poly3ntt_impl_

template <class mint, class mint0, class mint1, class mint2>
using poly3ntt = poly<poly3ntt_impl_::cconv_3ntt, mint, mint0, mint1, mint2>;

}  // namespace tifa_libs::math

#endif