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

  constexpr u64 idx(u64 n) const { return n <= sqm ? s - n : div_u64d(m, n); }

 public:
  // m^{3/2} in u64
  explicit constexpr min25_sieve(u64 m) : m(m), sqm(isqrt(m)) {
    assert(m < (1ll << 42));
    if (m) {
      u64 hls = div_u64d(m, sqm);
      if (hls != 1 && div_u64d(m, hls - 1) == sqm) --hls;
      s = hls + sqm;
      p = prime_seq((u32)sqm);
    }
  }

  constexpr vec<T> sum_pk(u32 k) const {
    auto sik = sum_ik<T>[k];
    if (!m) return {};
    u64 hls = div_u64d(m, sqm);
    if (hls != 1 && div_u64d(m, hls - 1) == sqm) --hls;
    vec<T> h(s);
    for (u64 i = 1; i < hls; ++i) h[i] = sik(div_u64d(m, i)) - 1;
    for (u64 i = 1; i <= sqm; ++i) h[s - i] = sik(i) - 1;
    for (u32 x : p) {
      T _ = x, pi = h[s - x + 1];
      _ = qpow(_, k);
      u64 x2 = u64(x) * x, mx = std::min(hls, div_u64d(m, x2) + 1);
      for (u64 i = 1, ix = x; i < mx; ++i, ix += x) h[i] -= ((ix < hls ? h[ix] : h[s - div_u64d(m, ix)]) - pi) * _;
      for (u64 n = sqm; n >= x2; --n) h[s - n] -= (h[s - div_u64d(n, x)] - pi) * _;
    }
    assert(h.size() == s);
    return h;
  }

  constexpr T run(vec<T> fprime) const {
    if (!m) return {};
    assert(fprime.size() == s);
    T ans = fprime[idx(m)] + 1;
    auto dfs = [&, this](auto&& dfs, u32 i, u32 c, u64 prod, T cur) -> void {
      ans += cur * f(p[i], c + 1);
      u64 lim = div_u64d(m, prod);
      if (lim >= (u64)p[i] * p[i]) dfs(dfs, i, c + 1, p[i] * prod, cur);
      cur *= f(p[i], c);
      ans += cur * (fprime[idx(lim)] - fprime[idx(p[i])]);
      u32 j = i + 1;
      for (; j < p.size() && (u64)p[j] * p[j] * p[j] <= lim; ++j) dfs(dfs, j, 1, prod * p[j], cur);
      for (; j < p.size() && (u64)p[j] * p[j] <= lim; ++j) {
        T sm = f(p[j], 2);
        u64 id1 = idx(div_u64d(lim, p[j])), id2 = idx(p[j]);
        ans += cur * (sm += f(p[j], 1) * (fprime[id1] - fprime[id2]));
      }
    };
    for (u32 i = 0; i < p.size(); ++i) dfs(dfs, i, 1, p[i], 1);
    return ans;
  }
};

}  // namespace tifa_libs::math

#endif