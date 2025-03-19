#ifndef TIFALIBS_COMB_QBINOM
#define TIFALIBS_COMB_QBINOM

#include "binom.hpp"
#include "gen_invseq.hpp"

namespace tifa_libs::math {

template <class mint, class fact = fact_helper<mint>>
struct qbinom : binom<mint, fact> {
  using fact_t = fact;
  vec<mint> qfact, iqfact;

  CEXPE qbinom(u32 q, u32 max_m = fact::DEFUALT_MAX) NE : binom<mint, fact>(max_m), qfact(2) {
    assert(q), qfact[0] = qfact[1] = 1;
    mint x = 1;
    flt_ (u32, i, 2, max_m + 1)
      if ((x = x * q + 1).val()) qfact.push_back(x);
      else break;
    flt_ (u32, i, 3, (u32)qfact.size()) qfact[i] *= qfact[i - 1];
    iqfact = gen_invseq(qfact);
  }

  // $\binom{m}{n}_q$
  CEXP mint qmCn(uint_c auto m, uint_c auto n) CNE {
    if (m < n) return 0;
    if (m < qfact.size()) return qfact[(usz)m] * iqfact[(usz)n] * iqfact[(usz)(m - n)];
    return this->mCn(m / qfact.size(), n / qfact.size()) * qmCn(m % qfact.size(), n % qfact.size());
  }
  // $\binom{m}{n}_q$
  template <sint_c T>
  CEXP mint qmCn(T m, T n) CNE { return m < n || n < 0 ? 0 : qmCn(to_uint_t<T>(m), to_uint_t<T>(n)); }
};

}  // namespace tifa_libs::math

#endif