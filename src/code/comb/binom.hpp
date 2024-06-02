#ifndef TIFALIBS_COMB_BINOM
#define TIFALIBS_COMB_BINOM

#include "../util/traits.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

template <class mint>
struct Binom {
  const vec<mint> fact, ifact;

  static CEXP u64 mod() { return mint::mod(); }
  explicit CEXP Binom(u32 max_m) : fact(gen_fact<mint>(max_m + 1)), ifact(gen_ifact<mint>(max_m + 1)) {}

  // $\binom{m}{n}$
  template <uint_c T>
  CEXP mint mCn(T m, T n) const { return m < n ? 0 : mPn(m, n) * ifact[(usz)n]; }
  // $\binom{m}{n}$
  template <sint_c T>
  CEXP mint mCn(T m, T n) const { return m < n || n < 0 ? 0 : mCn(to_uint_t<T>(m), to_uint_t<T>(n)); }
  // $\binom{m}{n} \cdot n!$
  template <uint_c T>
  CEXP mint mPn(T m, T n) const { return m < n ? 0 : fact[(usz)m] * ifact[(usz)(m - n)]; }
  // $\binom{m}{n} \cdot n!$
  template <sint_c T>
  CEXP mint mPn(T m, T n) const { return m < n || n < 0 ? 0 : mPn(to_uint_t<T>(m), to_uint_t<T>(n)); }
  // $[x^n] \frac{1}{(1-x)^m}$
  template <uint_c T>
  CEXP mint mHn(T m, T n) const { return n <= 0 ? n == 0 : mCn(m + n - 1, n); }
  // $[x^n] \frac{1}{(1-x)^m}$
  template <sint_c T>
  CEXP mint mHn(T m, T n) const { return m < 0 || n <= 0 ? n == 0 : mHn(to_uint_t<T>(m), to_uint_t<T>(n)); }
};

}  // namespace tifa_libs::math

#endif