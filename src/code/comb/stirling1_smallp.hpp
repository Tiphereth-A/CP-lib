#ifndef TIFALIBS_COMB_STIRLING1_SMALLP
#define TIFALIBS_COMB_STIRLING1_SMALLP

#include "lucas.hpp"

namespace tifa_libs::math {

template <class mint>
class Stirling1 {
  const Lucas<mint> mCn;
  vvec<mint> s;

 public:
  //! @param p MUST be prime
  explicit CEXP Stirling1() : mCn(), s(mint::mod()) {
    u32 p = mint::mod();
    assert(p < 32768);
    s[0] = {1};
    flt_ (u32, i, 1, p) {
      s[i].assign(i + 1, 0);
      fle_ (u32, j, 0, i) {
        if (j) s[i][j] += s[i - 1][j - 1];
        if (j < i) s[i][j] += s[i - 1][j] * (p - i + 1);
      }
    }
  }

  static CEXP u32 mod() { return mint::mod(); }
  template <bool with_sgn = true>
  CEXP mint operator()(i64 m_, i64 n_) const {
    if (n_ < 0 || n_ > m_) return 0;
    const u32 p = mod();
    const u64 m = (u64)m_, n = (u64)n_;
    const u64 i = m / p;
    if (i > n) return 0;
    u64 a = (n - i) / (p - 1);
    const u32 j = m % p;
    u32 b = (n - i) % (p - 1);
    if (!b && j) {
      b += p - 1;
      if (a) --a;
      else return 0;
    }
    if (i < a || b > j) return 0;
    mint res = mCn((i64)i, (i64)a) * s[j][b];
    if CEXP (with_sgn)
      if ((i + a) & 1) res = -res;
    return res;
  }
};

}  // namespace tifa_libs::math

#endif