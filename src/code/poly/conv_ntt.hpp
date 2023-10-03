#ifndef TIFALIBS_POLY_CONV_NTT
#define TIFALIBS_POLY_CONV_NTT

#include "../util/util.hpp"

#include "ntt.hpp"

namespace tifa_libs::math {

template <class mint>
inline vec<mint> conv_ntt(vec<mint> l, vec<mint> r, size_t ans_size) {
  static NTT<mint> ntt;
  ntt.bzr(std::min(l.size() + r.size() - 1, ans_size));
  ntt.dif(l);
  ntt.dif(r);
  for (size_t i = 0; i < ntt.size(); ++i) l[i] *= r[i];
  ntt.dit(l);
  l.resize(ans_size);
  return l;
}
template <class mint>
inline vec<mint> conv_ntt(vec<mint> const &l, vec<mint> const &r) { return conv_ntt(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif