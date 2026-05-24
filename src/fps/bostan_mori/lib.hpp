#pragma once

#include "../../conv/trans/ntt_doubling/lib.hpp"
#include "../ds/poly_c/lib.hpp"

namespace tifa_libs {
namespace bostan_mori_impl_ {
template <class ccore_t, class T>
vec<T> coeff_(ccore_t CR core, ccore_t CR core2, vec<T>& q, u64 n, u32 d) NE {
  cu32 len = core.size();
  vec<T> s(len * 2);
  if (!n) {
    vec<T> res(d);
    res.back() = len * std::reduce(q.begin(), q.begin() + len, T(0)).inv();
    return res;
  }
  ntt_doubling(core, q, len);
  vec<T> a(len * 2);
  flt_ (u32, i, len / 2, len) a[i * 2 + 1] = a[i * 2] = q[i * 2] * q[i * 2 + 1];
  flt_ (u32, i, 0, len) a[i] = q[i * 2] * q[i * 2 + 1];
  vec<T> w = coeff_(core, core2, a, n / 2, d);
  s = vec<T>(len * 2);
  for (u32 i = (n & 1) ^ 1, j = 0; j < d; ++j, i += 2) s[i] = w[j];
  core2.dif(s);
  flt_ (u32, i, 0, len * 2) s[i] *= q[i ^ 1];
  core2.dit(s);
  return vec<T>(begin(s) + d, begin(s) + d * 2);
}
}  // namespace bostan_mori_impl_

// @return [x^k]p/q
template <poly_c poly_t>
CEXP auto bostan_mori(u64 n, poly_t CR p, poly_t CR q) NE {
  if CEXP (assert(p.size() == q.size() - 1 && !p.is_zero()); poly_t::ccore_t::ct_cat != CCORE::NTT) {
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
    auto& core = poly_t::conv_core;
    auto core2 = core;
    cu32 m = (u32)q.size();
    core.bzr(m), core2.bzr(core.size() * 2);
    auto q_ = q;
    core.dif(q_), q_.resize(core2.size());
    auto iq = bostan_mori_impl_::coeff_(core, core2, q_, n, m - 1);
    TPN poly_t::val_t res = 0;
    flt_ (u32, i, 0, iq.size()) res += p[i] * iq[iq.size() - 1 - i];
    return res;
  }
}

}  // namespace tifa_libs
