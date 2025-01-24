#ifndef TIFALIBS_CONV_CONV_NTT_LARGE
#define TIFALIBS_CONV_CONV_NTT_LARGE

#include "conv_dft.hpp"

namespace tifa_libs::math {

template <ntt_c NTT_t, std::same_as<TPN NTT_t::data_t> mint>
CEXP vec<mint> conv_ntt_large(NTT_t &ntt, vec<mint> l, vec<mint> r, u32 ans_size = 0) NE {
  const u32 n = (u32)l.size(), m = (u32)r.size(), len = NTT_t::max_size;
  if (n + m - 1 <= len) return conv_dft<NTT_t, mint>(ntt, l, r, ans_size);
  if (!ans_size) ans_size = n + m - 1;
  ntt.bzr(len);
  vvec<mint> as, bs;
  for (u32 i = 0; i < l.size(); i += len / 2) {
    vec<mint> v{l.begin() + i, l.begin() + min(i + len / 2, (u32)l.size())};
    ntt.dif(v), as.push_back(v);
  }
  for (u32 i = 0; i < r.size(); i += len / 2) {
    vec<mint> v{r.begin() + i, r.begin() + min(i + len / 2, (u32)r.size())};
    ntt.dif(v), bs.push_back(v);
  }
  vvec<mint> cs(as.size() + bs.size() - 1, vec<mint>(len));
  flt_ (u32, i, 0, (u32)as.size())
    flt_ (u32, j, 0, (u32)bs.size())
      flt_ (u32, k, 0, len) cs[i + j][k] += as[i][k] * bs[j][k];
  for (auto &v : cs) ntt.dit(v);
  vec<mint> c(l.size() + r.size() - 1);
  flt_ (u32, i, 0, (u32)cs.size()) {
    const u32 ofs = len / 2 * i;
    flt_ (u32, j, 0, min(len, (u32)c.size() - ofs)) c[j + ofs] += cs[i][j];
  }
  c.resize(ans_size);
  return c;
}
template <class NTT_t, std::same_as<TPN NTT_t::data_t> mint, class T = u64>
CEXP vec<mint> conv_ntt_large_u64(NTT_t &ntt, vec<T> CR l, vec<T> CR r, u32 ans_size = 0) NE {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  vec<mint> l_, r_;
  for (l_.reserve(l.size()); auto i : l) l_.push_back(i);
  for (r_.reserve(r.size()); auto i : r) r_.push_back(i);
  return conv_ntt_large(ntt, l_, r_, ans_size);
}

}  // namespace tifa_libs::math

#endif