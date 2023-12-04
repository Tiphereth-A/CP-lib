#ifndef TIFALIBS_COMB_BINOM
#define TIFALIBS_COMB_BINOM

#include "../util/traits.hpp"
#include "gen_fact.hpp"
#include "gen_ifact.hpp"

namespace tifa_libs::math {

template <class mint>
struct Binom {
  const vec<mint> fact, ifact;

  Binom(u32 max_m) : fact(gen_fact<mint>(max_m)), ifact(gen_ifact<mint>(max_m)) {}

  constexpr static u64 mod() { return mint::mod(); }

  // \binom{m}{n}
  template <class T, std::enable_if_t<is_uint<T>::value>* = nullptr>
  mint mCn(T m, T n) const { return m < n ? 0 : mPn(m, n) * ifact[(usz)n]; }
  // \binom{m}{n}
  template <class T, std::enable_if_t<is_sint<T>::value>* = nullptr>
  mint mCn(T m, T n) const { return m < n || n < 0 ? 0 : mCn(to_uint_t<T>(m), to_uint_t<T>(n)); }

  // \binom{m}{n} * n!
  template <class T, std::enable_if_t<is_uint<T>::value>* = nullptr>
  mint mPn(T m, T n) const { return m < n ? 0 : fact[(usz)m] * ifact[(usz)(m - n)]; }
  // \binom{m}{n} * n!
  template <class T, std::enable_if_t<is_sint<T>::value>* = nullptr>
  mint mPn(T m, T n) const { return m < n || n < 0 ? 0 : mPn(to_uint_t<T>(m), to_uint_t<T>(n)); }

  // [x^n] 1 / (1-x)^m
  template <class T, std::enable_if_t<is_uint<T>::value>* = nullptr>
  mint mHn(T m, T n) const { return n <= 0 ? n == 0 : mCn(m + n - 1, n); }
  // [x^n] 1 / (1-x)^m
  template <class T, std::enable_if_t<is_sint<T>::value>* = nullptr>
  mint mHn(T m, T n) const { return m < 0 || n <= 0 ? n == 0 : mHn(to_uint_t<T>(m), to_uint_t<T>(n)); }
};

}  // namespace tifa_libs::math

#endif