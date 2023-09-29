#ifndef TIFALIBS_POLY_CONV_NTT
#define TIFALIBS_POLY_CONV_NTT

#include "../util/util.hpp"

#include "../bit/bceil.hpp"
#include "ntt.hpp"

namespace tifa_libs::math {

template <class mint>
inline vec<mint> conv_ntt(vec<mint> l, vec<mint> r, size_t ans_size) {
  static NTT<mint> ntt;
  size_t n = bit::bceil(ans_size);
  l.resize(n);
  r.resize(n);
  ntt(l);
  ntt(r);
  for (size_t i = 0; i < n; ++i) l[i] *= r[i];
  ntt<true>(l);
  l.resize(ans_size);
  return l;
}
template <class mint>
inline vec<mint> conv_ntt(vec<mint> l, vec<mint> r) { return conv_ntt(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif