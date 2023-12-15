#ifndef TIFALIBS_COMB_STIRLING2_SMALLP
#define TIFALIBS_COMB_STIRLING2_SMALLP

#include "lucas.hpp"

namespace tifa_libs::math {

template <class mint>
class Stirling2 {
  Lucas<mint> mCn;
  vvec<mint> S;

 public:
  //! @param p MUST be prime
  explicit constexpr Stirling2() : mCn(), S(mint::mod()) {
    u32 p = mint::mod();
    assert(p < 32768);
    S[0] = {1};
    for (u32 i = 1; i < p; ++i) {
      S[i].assign(i + 1, 0);
      for (u32 j = 0; j <= i; ++j) {
        if (j) S[i][j] += S[i - 1][j - 1];
        if (j < i) S[i][j] += S[i - 1][j] * j;
      }
    }
  }

  static constexpr u32 mod() { return mint::mod(); }
  constexpr mint operator()(i64 m_, i64 n_) const {
    if (n_ < 0 || n_ > m_) return 0;
    if (!m_) return 1;
    u32 p = mod();
    u64 m = (u64)m_, n = (u64)n_, i = n / p;
    if (m < i) return 0;
    u64 a = (m - i) / (p - 1);
    u32 j = n % p, b = (m - i) % (p - 1);
    if (!b) {
      b += p - 1;
      if (a) --a;
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