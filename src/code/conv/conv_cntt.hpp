#ifndef TIFALIBS_CONV_CONV_CNTT
#define TIFALIBS_CONV_CONV_CNTT

#include "../util/util.hpp"
#include "cntt.hpp"

namespace tifa_libs::math {

template <class mint>
inline vec<mint> conv_cntt(vec<mint> const &l, vec<mint> const &r, usz ans_size) {
  static CNTT<mint> cntt;
  cntt.bzr(std::min(l.size() + r.size() - 1, ans_size));
  vec<std::complex<mint>> v(cntt.size());
  for (usz i = 0, ie = std::min(l.size(), cntt.size()); i < ie; ++i) v[i].real(l[i]);
  for (usz i = 0, ie = std::min(r.size(), cntt.size()); i < ie; ++i) v[i].imag(r[i]);
  cntt.dif(v);
  for (usz i = 0; i < cntt.size(); ++i) v[i] *= v[i];
  cntt.dit(v);
  vec<mint> res(ans_size);
  mint inv = mint{cntt.size() * 2}.inv();
  for (usz i = 0; i < ans_size; ++i) res[i] = v[i].imag() * inv;
  return res;
}
template <class mint>
inline vec<mint> conv_cntt(vec<mint> const &l, vec<mint> const &r) { return conv_cntt(l, r, l.size() + r.size() - 1); }

template <class mint, class T = u64>
inline vec<mint> conv_cntt(vec<T> const &l, vec<T> const &r, usz ans_size) {
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_cntt(l_, r_, ans_size);
}
template <class mint, class T = u64>
inline vec<mint> conv_cntt(vec<T> const &l, vec<T> const &r) { return conv_cntt<mint, T>(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif