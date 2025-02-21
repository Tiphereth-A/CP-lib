#ifndef TIFALIBS_CONV_CONV_MTT
#define TIFALIBS_CONV_CONV_MTT

#include "conv_naive.hpp"
#include "fft_r2.hpp"

namespace tifa_libs::math {

template <class mint, class FP>
CEXP vec<mint> conv_mtt(FFT_R2<FP> &fft, vec<mint> CR l, vec<mint> CR r, u32 ans_size = 0) NE {
  using C = TPN FFT_R2<FP>::data_t;
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (min(l.size(), r.size()) < CONV_NAIVE_THRESHOLD) return conv_naive(l, r, ans_size);
  if (l.size() == 1) {
    vec<mint> ans = r;
    for (ans.resize(ans_size); auto &i : ans) i *= l[0];
    return ans;
  }
  if (r.size() == 1) {
    vec<mint> ans = l;
    for (ans.resize(ans_size); auto &i : ans) i *= r[0];
    return ans;
  }
  fft.bzr(max({(u32)l.size(), (u32)r.size(), min(u32(l.size() + r.size() - 1), ans_size)}));
  const u32 n = fft.size();
  const int OFS = ((int)sizeof(decltype(mint::mod())) * 8 - std::countl_zero(mint::mod() - 1) + 1) / 2;
  const u32 MSK = ((1u << OFS) - 1);
  vec<mint> ans(ans_size);
  vec<C> a(n), b(n);
  flt_ (u32, i, 0, (u32)l.size()) a[i] = {(FP)(l[i].val() & MSK), (FP)(l[i].val() >> OFS)};
  flt_ (u32, i, 0, (u32)r.size()) b[i] = {(FP)(r[i].val() & MSK), (FP)(r[i].val() >> OFS)};
  fft.dif(a), fft.dif(b);
  {
    vec<C> p(n), q(n);
    for (u32 i = 0, j; i < n; ++i) {
      j = (n - i) & (n - 1);
      C da = (a[i] + std::conj(a[j])) * C(.5, 0), db = (a[i] - std::conj(a[j])) * C(0, -.5),
        dc = (b[i] + std::conj(b[j])) * C(.5, 0), dd = (b[i] - std::conj(b[j])) * C(.5, 0);
      p[j] = da * dc + da * dd;
      q[j] = db * dc + db * dd;
    }
    a = p, b = q;
  }
  fft.dif(a), fft.dif(b);
  flt_ (u32, i, 0, ans_size) {
    const i64 da = (i64)(a[i].real() / (FP)n + .5) % mint::smod(),
              db = (i64)(a[i].imag() / (FP)n + .5) % mint::smod(),
              dc = (i64)(b[i].real() / (FP)n + .5) % mint::smod(),
              dd = (i64)(b[i].imag() / (FP)n + .5) % mint::smod();
    ans[i] = da + ((db + dc) << OFS) % mint::smod() + (dd << (OFS * 2)) % mint::smod();
  }
  return ans;
}

}  // namespace tifa_libs::math

#endif