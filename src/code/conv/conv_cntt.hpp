#ifndef TIFALIBS_CONV_CONV_CNTT
#define TIFALIBS_CONV_CONV_CNTT

#include "cntt.hpp"
#include "conv_naive.hpp"

namespace tifa_libs::math {

template <class mint, i64 M = -1>
constexpr vec<mint> conv_cntt(CNTT<mint, M> &cntt, vec<mint> const &l, vec<mint> const &r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (ans_size < 32) return conv_naive(l, r, ans_size);
  cntt.bzr(std::max({(u32)l.size(), (u32)r.size(), std::min(u32(l.size() + r.size() - 1), ans_size)}));
  vec<gint<mint, M>> v(cntt.size());
  for (u32 i = 0, ie = std::min((u32)l.size(), cntt.size()); i < ie; ++i) v[i].real(l[i]);
  for (u32 i = 0, ie = std::min((u32)r.size(), cntt.size()); i < ie; ++i) v[i].imag(r[i]);
  cntt.dif(v);
  for (u32 i = 0; i < cntt.size(); ++i) v[i] *= v[i];
  cntt.dit(v);
  vec<mint> res(ans_size);
  mint inv = mint{cntt.size() * 2}.inv();
  for (u32 i = 0; i < ans_size; ++i) res[i] = v[i].imag() * inv;
  return res;
}
template <class mint, i64 M = -1>
constexpr vec<mint> conv_cntt(CNTT<mint, M> &cntt, vecu64 const &l, vecu64 const &r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_cntt(cntt, l_, r_, ans_size);
}

}  // namespace tifa_libs::math

#endif