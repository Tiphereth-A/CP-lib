#ifndef TIFALIBS_CONV_CONV_DFT
#define TIFALIBS_CONV_CONV_DFT

#include "../util/traits_math.hpp"
#include "conv_naive.hpp"

namespace tifa_libs::math {

template <dft_c DFT_t, std::same_as<TPN DFT_t::data_t> DFT_data_t>
CEXP vec<DFT_data_t> conv_dft(DFT_t& dft, vec<DFT_data_t> l, vec<DFT_data_t> r, u32 ans_size = 0) NE {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (min(l.size(), r.size()) < CONV_NAIVE_THRESHOLD) return conv_naive(l, r, ans_size);
  dft.bzr(max({(u32)l.size(), (u32)r.size(), min(u32(l.size() + r.size() - 1), ans_size)}));
  dft.dif(l), dft.dif(r);
  flt_ (u32, i, 0, dft.size()) l[i] *= r[i];
  dft.dit(l), l.resize(ans_size);
  return l;
}
template <class DFT_t, class mint, class T = u64>
CEXP vec<mint> conv_dft_um(DFT_t& dft, vec<T> CR l, vec<T> CR r, u32 ans_size = 0) NE {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  vec<mint> l_, r_;
  for (l_.reserve(l.size()); auto CR i : l) l_.push_back(i);
  for (r_.reserve(r.size()); auto CR i : r) r_.push_back(i);
  return conv_dft(dft, l_, r_, ans_size);
}

}  // namespace tifa_libs::math

#endif