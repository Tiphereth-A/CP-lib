#ifndef TIFALIBS_COMB_STIRLING1_SMALLP
#define TIFALIBS_COMB_STIRLING1_SMALLP

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint, class fact = fact_helper<mint>, bool with_sgn = true>
class Stirling1 {
  const binom<mint, fact> mCn;
  vvec<mint> s;

 public:
  static CEXP u32 mod() NE { return mint::mod(); }
  //! @param p MUST be prime
  CEXPE Stirling1() NE : mCn(mint::mod()), s(mint::mod()) {
    u32 p = mint::mod();
    assert(p < 32768), s[0] = {1};
    flt_ (u32, i, 1, p) {
      s[i].assign(i + 1, 0);
      flt_ (u32, j, 0, i + 1) {
        if (j) s[i][j] += s[i - 1][j - 1];
        if (j < i) s[i][j] += s[i - 1][j] * (p - i + 1);
      }
    }
  }

  template <std::signed_integral T>
  CEXP mint operator()(T m_, T n_) CNE {
    if (n_ < 0 || n_ > m_) return 0;
    const u32 p = mod();
    const u64 m = (u64)m_, n = (u64)n_, i = m / p;
    if (i > n) return 0;
    u64 a = (n - i) / (p - 1);
    const u32 j = u32(m % p);
    u32 b = u32((n - i) % (p - 1));
    if (!b && j) {
      if (b += p - 1; a) --a;
      else return 0;
    }
    if (i < a || b > j) return 0;
    mint res = mCn.lucas(i, a) * s[j][b];
    if CEXP (with_sgn)
      if ((i + a) & 1) res = -res;
    return res;
  }
  template <std::unsigned_integral T>
  CEXP mint operator()(T m_, T n_) CNE { return operator()(std::make_signed_t<T>(m_), std::make_signed_t<T>(n_)); }
};

}  // namespace tifa_libs::math

#endif