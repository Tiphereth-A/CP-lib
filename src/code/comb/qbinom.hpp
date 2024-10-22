#ifndef TIFALIBS_COMB_QBINOM
#define TIFALIBS_COMB_QBINOM

#include "binom.hpp"
#include "gen_invseq.hpp"

namespace tifa_libs::math {

template <class mint>
struct QBinom {
  vec<mint> qfact, iqfact;
  Binom<mint> binom;

  static CEXP u64 mod() { return mint::mod(); }
  CEXPE QBinom(u32 max_m, u32 q) : qfact(2) {
    assert(q), qfact[0] = qfact[1] = 1;
    mint x = 1;
    fle_ (u32, i, 2, max_m)
      if ((x = x * q + 1).val()) qfact.push_back(x);
      else break;
    fle_ (u32, i, 3, u32(qfact.size() - 1)) qfact[i] *= qfact[i - 1];
    iqfact = gen_invseq(qfact), binom = Binom<mint>(u32((max_m + qfact.size() - 2) / (qfact.size() - 1)));
  }

  // $\binom{m}{n}_q$
  template <uint_c T>
  CEXP mint qmCn(T m, T n) const {
    if (m < n) return 0;
    if (m < qfact.size()) return qfact[(usz)m] * iqfact[(usz)n] * iqfact[(usz)(m - n)];
    return binom.mCn(m / qfact.size(), n / qfact.size()) * qmCn(m % qfact.size(), n % qfact.size());
  }
  // $\binom{m}{n}_q$
  template <sint_c T>
  CEXP mint qmCn(T m, T n) const { return m < n || n < 0 ? 0 : qmCn(to_uint_t<T>(m), to_uint_t<T>(n)); }
};

}  // namespace tifa_libs::math

#endif