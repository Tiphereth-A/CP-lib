#ifndef TIFALIBS_COMB_EXLUCAS
#define TIFALIBS_COMB_EXLUCAS

#include "../math/isqrt.hpp"
#include "../math/qpow_mod.hpp"
#include "../nt/crt.hpp"
#include "gen_invseq.hpp"

namespace tifa_libs::math {

// Calculate $\binom{m}{n} \bmod p$, p can be ANY INTEGER
class ExLucas {
  struct TIFA {
    const u32 p, q;
    const bool no_proot;
    u64 m_;
    vecuu facp, ifacp;
    CEXP TIFA(u32 p, u32 q) : p(p), q(q), no_proot(p == 2 && q >= 3) {
      assert(p <= 100'000'000 && q > 0), m_ = 1;
      while (q--) (m_ *= p), assert(m_ <= 100'000'000);
      facp.resize(m_), facp[0] = facp[1] = 1;
      flt_ (u64, i, 2, m_)
        if (i % p == 0) facp[i] = facp[i - 1], facp[i + 1] = facp[i - 1] * (i + 1) % m_, ++i;
        else facp[i] = facp[i - 1] * i % m_;
      ifacp = gen_invseq(facp, m_);
    }
    CEXP u64 operator()(i64 m, i64 n) const {
      if (m < n || n < 0) return 0;
      i64 r = m - n;
      i32 e0 = 0, eq = 0;
      u32 i = 0;
      u64 res = 1;
      while (m) {
        res = res * facp[(u64)m % m_] % m_ * ifacp[(u64)n % m_] % m_ * ifacp[(u64)r % m_] % m_, m /= p, n /= p, r /= p;
        if (i32 eps = (i32)(m - n - r); (e0 += eps) >= (i32)q) return 0;
        else if (++i >= q) eq += eps;
      }
      return (!no_proot && (eq & 1) ? m_ - res : res) * qpow_mod(p, (u32)e0, m_) % m_;
    }
  };
  const u32 m_;
  vecuu ms;
  vec<TIFA> cs;

 public:
  CEXPE ExLucas(u32 md) : m_(md) {
    assert(md < 100'000'000);
    flt_ (u32, i, 2, isqrt(md) + 1)
      if (md % i == 0) {
        u32 j = 0, k = 1;
        while (md % i == 0) md /= i, ++j, k *= i;
        ms.push_back(k), cs.emplace_back(i, j);
      }
    if (md > 1) ms.push_back(md), cs.emplace_back(md, 1);
  }

  CEXP u64 operator()(i64 m, i64 n) const {
    if (m_ == 1 || m < n || n < 0) return 0;
    vecii b;
    for (b.reserve(cs.size()); auto CR i : cs) b.push_back((i64)i(m, n));
    return crt(b, ms)->first;
  }
};

}  // namespace tifa_libs::math

#endif