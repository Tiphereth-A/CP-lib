#ifndef TIFA_LIBS_MATH_NTH_TERM_LREC
#define TIFA_LIBS_MATH_NTH_TERM_LREC

#include "../poly/bostan_mori.hpp"
#include "berlekamp_massey.hpp"

namespace tifa_libs::math {

template <class pdata, class mint = typename pdata::value_type>
mint nth_term_lrec(u64 n, vec<mint> const& a, vec<mint> const& bm) {
  if (n < a.size()) return a[n];
  assert(!bm.empty() && bm[0] != 0);
  auto p = poly<pdata>(a).pre(u32(bm.size() - 1)) * poly<pdata>(bm);
  p.resize(u32(bm.size() - 1));
  return bostan_mori(n, poly<pdata>(bm), poly<pdata>(p));
}
template <class pdata, class mint = typename pdata::value_type>
mint nth_term_lrec(u64 n, vec<mint> const& a) {
  if (n < a.size()) return a[n];
  auto bm = berlekamp_massey(a);
  return nth_term_lrec<pdata>(n, a, bm);
}

}  // namespace tifa_libs::math

#endif