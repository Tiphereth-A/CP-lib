#ifndef TIFA_LIBS_MATH_NTH_TERM_LREC
#define TIFA_LIBS_MATH_NTH_TERM_LREC

#include "../poly/bostan_mori.hpp"
#include "berlekamp_massey.hpp"

namespace tifa_libs::math {

template <class pdata, class mint = typename pdata::value_type>
mint nth_term_lrec(u64 n, vec<mint> const& a, vec<mint> const& bm) {
  if (n < a.size()) return a[n];
  assert(!bm.empty() && bm[0] == 1);
  poly<pdata> q(bm);
  q.strip();
  return bostan_mori(n, (poly<pdata>(a) * q).pre(q.size() - 1), q);
}
template <class pdata, class mint = typename pdata::value_type>
mint nth_term_lrec(u64 n, vec<mint> const& a) {
  if (n < a.size()) return a[n];
  auto bm = berlekamp_massey(a);
  return nth_term_lrec<pdata>(n, a, bm);
}

}  // namespace tifa_libs::math

#endif