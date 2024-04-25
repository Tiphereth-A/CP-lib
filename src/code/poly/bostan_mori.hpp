#ifndef TIFALIBS_POLY_BOSTAN_MORI
#define TIFALIBS_POLY_BOSTAN_MORI

#include "../conv/ntt_doubling.hpp"
#include "poly.hpp"

namespace tifa_libs::math {
namespace bostan_mori_impl_ {
template <class ccore_t, class T>
vec<T> coeff_(ccore_t CR core, ccore_t CR core2, vec<T>& q, u64 n, u32 d) {
  static u32 len = core.size();
  static vec<T> s(len * 2);
  static CEXP T inv2 = (T::mod() + 1) / 2;
  if (!n) {
    vec<T> res(d);
    T q0 = 0;
    flt_ (u32, i, 0, len) q0 += q[i];
    res.back() = len * q0.inv();
    return res;
  }
  ntt_doubling(core, q, len);
  vec<T> a(len * 2);
  for (u32 i = 0; i < len * 2; ++i) a[i] = q[i] * q[i ^ 1];
  for (u32 i = 0, j = 0; i < len * 2; i += 2, ++j) a[j] = inv2 * (a[i] + a[i + 1]);
  vec<T> w = coeff_(core, core2, a, n / 2, d);
  for (u32 i = 0; i < len * 2; ++i) s[i] = 0;
  for (u32 i = (n & 1) ^ 1, j = 0; j < d; ++j, i += 2) s[i] = w[j];
  core2.dif(s);
  for (u32 i = 0; i < len * 2; ++i) s[i] *= q[i ^ 1];
  core2.dit(s);
  return vec<T>(s.begin() + d, s.begin() + d * 2);
}
}  // namespace bostan_mori_impl_

// @return [x^k]p/q
template <class mint, class ccore>
CEXP auto bostan_mori(u64 n, poly<mint, ccore> CR p, poly<mint, ccore> CR q) {
  assert(p.size() == q.size() - 1 && !p.empty());
  if CEXP (ccore::ct_cat != ct_NTT) {
    auto p_ = p, q_ = q;
    while (n) {
      auto _ = q_;
      for (u32 i = 1; i < _.size(); i += 2) _[i] = -_[i];
      auto s = p_ * _, t = q_ * _;
      for (u32 i = n & 1; i < s.size(); i += 2) p_[i / 2] = s[i];
      for (u32 i = 0; i < t.size(); i += 2) q_[i / 2] = t[i];
      n /= 2;
    }
    return p_[0];
  } else {
    auto& core = poly<mint, ccore>::conv_core;
    auto core2 = core;
    u32 m = (u32)q.size();
    core.bzr(m);
    core2.bzr(core.size() * 2);
    auto q_ = q.data();
    core.dif(q_);
    q_.resize(core2.size());
    auto iq = bostan_mori_impl_::coeff_(core, core2, q_, n, m - 1);
    mint res = 0;
    for (u32 i = 0, e = u32(iq.size() - 1); i <= e; ++i) res += p[i] * iq[e - i];
    return res;
  }
}

}  // namespace tifa_libs::math

#endif