#ifndef TIFALIBS_COMB_STIRLING2_SMALLP
#define TIFALIBS_COMB_STIRLING2_SMALLP

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint, class fact = fact_helper<mint>>
class Stirling2 {
  const binom<mint, fact> mCn;
  vvec<mint> S;

 public:
  //! @param p MUST be prime
  CEXPE Stirling2() NE : mCn(mint::mod()), S(mint::mod()) {
    u32 p = mint::mod();
    assert(p < 32768), S[0] = {1};
    flt_ (u32, i, 1, p) {
      S[i].assign(i + 1, 0);
      flt_ (u32, j, 0, i + 1) {
        if (j) S[i][j] += S[i - 1][j - 1];
        if (j < i) S[i][j] += S[i - 1][j] * j;
      }
    }
  }

  static CEXP u32 mod() NE { return mint::mod(); }
  template <std::signed_integral T>
  CEXP mint operator()(T m_, T n_) CNE {
    if (n_ < 0 || n_ > m_) return 0;
    if (!m_) return 1;
    const u32 p = mod();
    const u64 m = (u64)m_, n = (u64)n_, i = n / p;
    if (m < i) return 0;
    u64 a = (m - i) / (p - 1);
    const u32 j = u32(n % p);
    u32 b = u32((m - i) % (p - 1));
    if (!b) {
      if (b += p - 1; a) --a;
      else return 0;
    }
    if (j > b) return 0;
    if (b < p - 1) return mCn.lucas(a, i) * S[b][j];
    if (!j) return mCn.lucas(a, i - 1);
    return mCn.lucas(a, i) * S[p - 1][j];
  }
  template <std::unsigned_integral T>
  CEXP mint operator()(T m_, T n_) CNE { return operator()(std::make_signed_t<T>(m_), std::make_signed_t<T>(n_)); }
};

}  // namespace tifa_libs::math

#endif