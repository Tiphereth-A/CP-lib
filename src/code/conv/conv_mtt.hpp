#ifndef TIFALIBS_CONV_CONV_MTT
#define TIFALIBS_CONV_CONV_MTT

#include "../util/util.hpp"
#include "fft.hpp"

namespace tifa_libs::math {

template <class mint, class FP>
vec<mint> conv_mtt(FFT<FP> &fft, vec<mint> const &l, vec<mint> const &r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  using C = typename FFT<FP>::C;
  if (l.size() == 1) {
    vec<mint> ans = r;
    ans.resize(ans_size);
    for (auto &i : ans) i *= l[0];
    return ans;
  }
  if (r.size() == 1) {
    vec<mint> ans = l;
    ans.resize(ans_size);
    for (auto &i : ans) i *= r[0];
    return ans;
  }
  fft.bzr(std::max({(u32)l.size(), (u32)r.size(), std::min(u32(l.size() + r.size() - 1), ans_size)}));
  u32 n = fft.size();
  const int OFS = ((int)sizeof(decltype(mint::mod())) * 8 - std::countl_zero(mint::mod() - 1) + 1) / 2;
  const u32 MSK = ((1u << OFS) - 1);
  vec<mint> ans(ans_size);
  vec<C> a(n), b(n);
  for (u32 i = 0; i < l.size(); ++i) a[i] = {(FP)(l[i].val() & MSK), (FP)(l[i].val() >> OFS)};
  for (u32 i = 0; i < r.size(); ++i) b[i] = {(FP)(r[i].val() & MSK), (FP)(r[i].val() >> OFS)};
  fft.dif(a);
  fft.dif(b);
  {
    vec<C> p(n), q(n);
    for (u32 i = 0, j; i < n; ++i) {
      j = (n - i) & (n - 1);
      C da = (a[i] + std::conj(a[j])) * C(.5, 0), db = (a[i] - std::conj(a[j])) * C(0, -.5), dc = (b[i] + std::conj(b[j])) * C(.5, 0), dd = (b[i] - std::conj(b[j])) * C(.5, 0);
      p[j] = da * dc + da * dd;
      q[j] = db * dc + db * dd;
    }
    a = p;
    b = q;
  }
  fft.dif(a);
  fft.dif(b);
  for (u32 i = 0; i < ans_size; ++i) {
    i64 da = (i64)(a[i].real() / (FP)n + .5) % mint::mod(), db = (i64)(a[i].imag() / (FP)n + .5) % mint::mod(), dc = (i64)(b[i].real() / (FP)n + .5) % mint::mod(), dd = (i64)(b[i].imag() / (FP)n + .5) % mint::mod();
    ans[i] = da + ((db + dc) << OFS) % mint::mod() + (dd << (OFS * 2)) % mint::mod();
  }
  return ans;
}

}  // namespace tifa_libs::math

#endif