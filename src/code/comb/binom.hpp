#ifndef TIFALIBS_COMB_BINOM
#define TIFALIBS_COMB_BINOM

#include "../math/fact_helper.hpp"

namespace tifa_libs::math {

template <class mint, class fact = fact_helper<mint>>
requires std::same_as<mint, TPN fact::val_t>
struct binom {
  using fact_t = fact;

  CEXPE binom(u32 max_m = fact::DEFUALT_MAX) NE { fact::ensure(max_m + 1); }

  // $\binom{m}{n}$
  CEXP mint mCn(uint_c auto m, uint_c auto n) CNE { return m < n ? 0 : mPn(m, n) * fact::get_ifact(n); }
  // $\binom{m}{n}$
  template <sint_c T>
  CEXP mint mCn(T m, T n) CNE { return m < n || n < 0 ? 0 : mCn(to_uint_t<T>(m), to_uint_t<T>(n)); }
  //! mint::mod() must be prime
  template <int_c T>
  CEXP mint lucas(T m, T n) CNE {
    assert(mint::mod() > 1);
    auto f = [this](auto &&f, auto m, auto n) NE -> mint { return n == 0 ? 1 : this->mCn(m % fact::mod(), n % fact::mod()) * f(f, m / fact::mod(), n / fact::mod()); };
    return m < n || n < 0 ? 0 : f(f, to_uint_t<T>(m), to_uint_t<T>(n));
  }
  // $\binom{m}{n} \cdot n!$
  CEXP mint mPn(uint_c auto m, uint_c auto n) CNE { return m < n ? 0 : fact::get_fact(m) * fact::get_ifact(m - n); }
  // $\binom{m}{n} \cdot n!$
  template <sint_c T>
  CEXP mint mPn(T m, T n) CNE { return m < n || n < 0 ? 0 : mPn(to_uint_t<T>(m), to_uint_t<T>(n)); }
  // $[x^n] \frac{1}{(1-x)^m}$
  CEXP mint mHn(uint_c auto m, uint_c auto n) CNE { return n <= 0 ? n == 0 : mCn(m + n - 1, n); }
  // $[x^n] \frac{1}{(1-x)^m}$
  template <sint_c T>
  CEXP mint mHn(T m, T n) CNE { return m < 0 || n <= 0 ? n == 0 : mHn(to_uint_t<T>(m), to_uint_t<T>(n)); }
};

}  // namespace tifa_libs::math

#endif