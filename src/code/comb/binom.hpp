#ifndef TIFA_LIBS_MATH_BINOM
#define TIFA_LIBS_MATH_BINOM

#include "../math/mul_mod_u.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

class Binom {
  u64 m_;

 public:
  const vec<u64> fact, ifact;

  Binom(u64 mod, usz max_m) : m_(mod), fact(fact_mod_gen(max_m, mod)), ifact(ifact_mod_gen(max_m, mod)) {}

  constexpr u64 mod() const { return m_; }

  // \binom{m}{n}
  u64 mCn(u64 m, u64 n) const { return m < n ? 0 : mul_mod_u(mul_mod_u(fact[(usz)m], ifact[(usz)n], m_), ifact[(usz)(m - n)], m_); }
  // \binom{m}{n}
  u64 mCn(i64 m, i64 n) const { return m < n || n < 0 ? 0 : mCn((u64)m, (u64)n); }

  // \binom{m}{n} * n!
  u64 mPn(u64 m, u64 n) const { return m < n ? 0 : mul_mod_u(fact[(usz)m], ifact[(usz)(m - n)], m_); }
  // \binom{m}{n} * n!
  u64 mPn(i64 m, i64 n) const { return m < n || n < 0 ? 0 : mPn((u64)m, (u64)n); }

  // [x^n] 1 / (1-x)^m
  u64 mHn(u64 m, u64 n) const { return n <= 0 ? n == 0 : mCn(m + n - 1, n); }
  // [x^n] 1 / (1-x)^m
  u64 mHn(i64 m, i64 n) const { return m < 0 || n <= 0 ? n == 0 : mHn((u64)m, (u64)n); }
};

}  // namespace tifa_libs::math

#endif