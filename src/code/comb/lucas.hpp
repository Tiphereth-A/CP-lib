#ifndef TIFA_LIBS_MATH_LUCAS
#define TIFA_LIBS_MATH_LUCAS

#include "binom.hpp"

namespace tifa_libs::math {

class Lucas {
  Binom mCn;

  u64 lucas__(const Binom &mCn, u64 m, u64 n) const {
    const u64 m_ = mod();
    return n == 0 ? 1 : mCn.mCn(m % m_, n % m_) * lucas__(mCn, m / m_, n / m_) % m_;
  }

 public:
  // @param p MUSU be prime
  explicit Lucas(u32 p) : mCn(p, p) { assert(p > 1 && p < 10'000'000); }

  constexpr u64 mod() const { return mCn.mod(); }
  u64 operator()(i64 m, i64 n) const { return m < n || n < 0 ? 0 : lucas__(mCn, (u64)m, (u64)n); }
};

}  // namespace tifa_libs::math

#endif