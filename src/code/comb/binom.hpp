#ifndef TIFA_LIBS_MATH_BINOM
#define TIFA_LIBS_MATH_BINOM

#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

template <class mint>
struct Binom {
  const vec<mint> fact, ifact;

  Binom(usz max_m) : fact(gen_fact<mint>(max_m)), ifact(gen_ifact<mint>(max_m)) {}

  constexpr static u64 mod() { return mint::mod(); }

  // \binom{m}{n}
  mint mCn(u64 m, u64 n) const { return m < n ? 0 : mPn(m, n) * ifact[(usz)n]; }
  // \binom{m}{n}
  mint mCn(i64 m, i64 n) const { return m < n || n < 0 ? 0 : mCn((u64)m, (u64)n); }

  // \binom{m}{n} * n!
  mint mPn(u64 m, u64 n) const { return m < n ? 0 : fact[(usz)m] * ifact[(usz)(m - n)]; }
  // \binom{m}{n} * n!
  mint mPn(i64 m, i64 n) const { return m < n || n < 0 ? 0 : mPn((u64)m, (u64)n); }

  // [x^n] 1 / (1-x)^m
  mint mHn(u64 m, u64 n) const { return n <= 0 ? n == 0 : mCn(m + n - 1, n); }
  // [x^n] 1 / (1-x)^m
  mint mHn(i64 m, i64 n) const { return m < 0 || n <= 0 ? n == 0 : mHn((u64)m, (u64)n); }
};

}  // namespace tifa_libs::math

#endif