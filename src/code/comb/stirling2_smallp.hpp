#ifndef TIFALIBS_COMB_STIRLING2_SMALLP
#define TIFALIBS_COMB_STIRLING2_SMALLP

#include "lucas.hpp"

namespace tifa_libs::math {

template <class mint>
class Stirling2 {
  const Lucas<mint> mCn;
  vvec<mint> S;

 public:
  //! @param p MUST be prime
  explicit CEXP Stirling2() : mCn(), S(mint::mod()) {
    u32 p = mint::mod();
    assert(p < 32768);
    S[0] = {1};
    flt_ (u32, i, 1, p) {
      S[i].assign(i + 1, 0);
      fle_ (u32, j, 0, i) {
        if (j) S[i][j] += S[i - 1][j - 1];
        if (j < i) S[i][j] += S[i - 1][j] * j;
      }
    }
  }

  static CEXP u32 mod() { return mint::mod(); }
  CEXP mint operator()(i64 m_, i64 n_) const {
    if (n_ < 0 || n_ > m_) return 0;
    if (!m_) return 1;
    const u32 p = mod();
    const u64 m = (u64)m_, n = (u64)n_, i = n / p;
    if (m < i) return 0;
    u64 a = (m - i) / (p - 1);
    const u32 j = n % p;
    u32 b = (m - i) % (p - 1);
    if (!b) {
      if (b += p - 1; a) --a;
      else return 0;
    }
    if (j > b) return 0;
    if (b < p - 1) return mCn((i64)a, (i64)i) * S[b][j];
    if (!j) return mCn((i64)a, (i64)i - 1);
    return mCn((i64)a, (i64)i) * S[p - 1][j];
  }
};

}  // namespace tifa_libs::math

#endif