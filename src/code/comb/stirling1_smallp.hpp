#ifndef TIFA_LIBS_MATH_STIRLING1_SMALLP
#define TIFA_LIBS_MATH_STIRLING1_SMALLP

#include "lucas.hpp"

namespace tifa_libs::math {

template <class mint>
class Stirling1 {
  Lucas<mint> mCn;
  vvec<mint> s;

 public:
  //! @param p MUST be prime
  explicit Stirling1() : mCn(), s(mint::mod()) {
    u32 p = mint::mod();
    assert(p < 32768);
    s[0] = {1};
    for (u32 i = 1; i < p; ++i) {
      s[i].assign(i + 1, 0);
      for (u32 j = 0; j <= i; ++j) {
        if (j) s[i][j] += s[i - 1][j - 1];
        if (j < i) s[i][j] += s[i - 1][j] * (p - i + 1);
      }
    }
  }

  constexpr static u32 mod() { return mint::mod(); }
  template <bool with_sgn = true>
  mint operator()(i64 m_, i64 n_) const {
    if (n_ < 0 || n_ > m_) return 0;
    u32 p = mod();
    u64 m = (u64)m_, n = (u64)n_;
    u64 i = m / p;
    if (i > n) return 0;
    u64 a = (n - i) / (p - 1);
    u32 j = m % p, b = (n - i) % (p - 1);
    if (!b && j) {
      b += p - 1;
      if (a) --a;
      else return 0;
    }
    if (i < a || b > j) return 0;
    u32 x = (u32)mCn((i64)i, (i64)a), y = s[j][b], res = x * y % p;
    if constexpr (with_sgn)
      if (((i + a) & 1) && res) res = p - res;
    return res;
  }
};

}  // namespace tifa_libs::math

#endif