#ifndef TIFA_LIBS_MATH_STIRLING1_SMALLP
#define TIFA_LIBS_MATH_STIRLING1_SMALLP

#include "lucas.hpp"

namespace tifa_libs::math {

class Stirling1 {
  Lucas mCn;
  vvec<u32> s;

 public:
  //! @param p MUST be prime
  explicit Stirling1(u32 p) : mCn(p), s(p) {
    assert(p < 32768);
    s[0] = {1};
    for (u32 i = 1; i < p; ++i) {
      s[i].assign(i + 1, 0);
      for (u32 j = 0; j <= i; ++j) {
        if (j) s[i][j] += s[i - 1][j - 1];
        if (j < i) s[i][j] += s[i - 1][j] * (p - i + 1);
        s[i][j] %= p;
      }
    }
  }

  constexpr u32 mod() const { return (u32)mCn.mod(); }
  u32 operator()(i64 m_, i64 n_) const {
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
    if (((i + a) & 1) && res) res = p - res;
    return res;
  }
};

}  // namespace tifa_libs::math

#endif