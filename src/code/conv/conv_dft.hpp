#ifndef TIFALIBS_CONV_CONV_DFT
#define TIFALIBS_CONV_CONV_DFT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class DFT_t, class mint>
vec<mint> conv_dft(DFT_t &dft, vec<mint> l, vec<mint> r, u32 ans_size) {
  dft.bzr(std::max({(u32)l.size(), (u32)r.size(), std::min(u32(l.size() + r.size() - 1), ans_size)}));
  dft.dif(l);
  dft.dif(r);
  for (u32 i = 0; i < dft.size(); ++i) l[i] *= r[i];
  dft.dit(l);
  l.resize(ans_size);
  return l;
}
template <class DFT_t, class mint>
vec<mint> conv_dft(DFT_t &dft, vec<mint> const &l, vec<mint> const &r) { return conv_dft(dft, l, r, u32(l.size() + r.size() - 1)); }
template <class DFT_t, class mint, class T = u64>
vec<mint> conv_dft(DFT_t &dft, vec<T> const &l, vec<T> const &r, u32 ans_size) {
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_dft(dft, l_, r_, ans_size);
}
template <class DFT_t, class mint, class T = u64>
vec<mint> conv_dft(DFT_t &dft, vec<T> const &l, vec<T> const &r) { return conv_dft<DFT_t, mint, T>(dft, l, r, u32(l.size() + r.size() - 1)); }

}  // namespace tifa_libs::math

#endif