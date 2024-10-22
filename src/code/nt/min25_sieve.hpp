#ifndef TIFALIBS_MATH_MIN25_SIEVE
#define TIFALIBS_MATH_MIN25_SIEVE

#include "../math/div64.hpp"
#include "../math/qpow.hpp"
#include "../math/sum_ik_flist.hpp"
#include "prime_seq.hpp"

namespace tifa_libs::math {

// f(p, c) = value of f(p^c)
template <class T, T (*f)(u64, u64)>
class min25_sieve {
  u64 m, sqm, s;
  vecu p;

  CEXP u64 idx(u64 n) const { return n <= sqm ? s - n : div_u64d(m, n); }

 public:
  // m^{3/2} in u64
  CEXPE min25_sieve(u64 m) : m(m), sqm(isqrt(m)) {
    if (assert(m < (1ll << 42)); m) {
      u64 hls = div_u64d(m, sqm);
      if (hls != 1 && div_u64d(m, hls - 1) == sqm) --hls;
      s = hls + sqm, p = prime_seq((u32)sqm);
    }
  }

  CEXP vec<T> sum_pk(u32 k) const {
    auto sik = sum_ik<T>[k];
    if (!m) return {};
    u64 hls = div_u64d(m, sqm);
    if (hls != 1 && div_u64d(m, hls - 1) == sqm) --hls;
    vec<T> h(s);
    flt_ (u64, i, 1, hls) h[i] = sik(div_u64d(m, i)) - 1;
    fle_ (u64, i, 1, sqm) h[s - i] = sik(i) - 1;
    for (u32 x : p) {
      T _ = x, pi = h[s - x + 1];
      _ = qpow(_, k);
      u64 x2 = u64(x) * x, mx = min(hls, div_u64d(m, x2) + 1);
      for (u64 i = 1, ix = x; i < mx; ++i, ix += x) h[i] -= ((ix < hls ? h[ix] : h[s - div_u64d(m, ix)]) - pi) * _;
      for (u64 n = sqm; n >= x2; --n) h[s - n] -= (h[s - div_u64d(n, x)] - pi) * _;
    }
    assert(h.size() == s);
    return h;
  }
  CEXP T run(vec<T> fprime) const {
    if (!m) return {};
    assert(fprime.size() == s);
    T ans = fprime[idx(m)] + 1;
    auto dfs = [&, this](auto&& dfs, u32 i, u32 c, u64 prod, T now) -> void {
      ans += now * f(p[i], c + 1);
      u64 lim = div_u64d(m, prod);
      if (lim >= (u64)p[i] * p[i]) dfs(dfs, i, c + 1, p[i] * prod, now);
      now *= f(p[i], c), ans += now * (fprime[idx(lim)] - fprime[idx(p[i])]);
      u32 j = i + 1;
      for (; j < p.size() && (u64)p[j] * p[j] * p[j] <= lim; ++j) dfs(dfs, j, 1, prod * p[j], now);
      for (; j < p.size() && (u64)p[j] * p[j] <= lim; ++j) {
        T _ = f(p[j], 2);
        u64 i1 = idx(div_u64d(lim, p[j])), i2 = idx(p[j]);
        ans += now * (_ += f(p[j], 1) * (fprime[i1] - fprime[i2]));
      }
    };
    flt_ (u32, i, 0, (u32)p.size()) dfs(dfs, i, 1, p[i], 1);
    return ans;
  }
};

}  // namespace tifa_libs::math

#endif