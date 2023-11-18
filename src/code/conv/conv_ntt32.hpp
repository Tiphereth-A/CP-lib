#ifndef TIFALIBS_CONV_CONV_NTT32
#define TIFALIBS_CONV_CONV_NTT32

#include "../util/util.hpp"
#include "ntt32.hpp"

namespace tifa_libs::math {

template <class mint>
vec<mint> conv_ntt32(vec<mint> l, vec<mint> r, u32 ans_size) {
  static NTT32<mint> ntt;
  ntt.bzr(std::max({l.size(), r.size(), std::min(l.size() + r.size() - 1, ans_size)}));
  ntt.dif(l);
  ntt.dif(r);
  for (u32 i = 0; i < ntt.size(); ++i) l[i] *= r[i];
  ntt.dit(l);
  l.resize(ans_size);
  return l;
}
template <class mint>
vec<mint> conv_ntt32(vec<mint> const &l, vec<mint> const &r) { return conv_ntt32(l, r, l.size() + r.size() - 1); }
template <class mint, class T = u32>
vec<mint> conv_ntt32(vec<T> const &l, vec<T> const &r, u32 ans_size) {
  static_assert(sizeof(T) <= 32);
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_ntt32(l_, r_, ans_size);
}
template <class mint, class T = u32>
vec<mint> conv_ntt32(vec<T> const &l, vec<T> const &r) { return conv_ntt32<mint, T>(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif