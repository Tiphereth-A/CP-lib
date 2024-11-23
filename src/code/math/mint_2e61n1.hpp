#ifndef TIFALIBS_MATH_MINT_2E61N1
#define TIFALIBS_MATH_MINT_2E61N1

#include "../util/traits.hpp"

namespace tifa_libs::math {

template <u64>
class mint_2e61n1 {
  static CEXP u64 MOD = (1ull << 61) - 1, _30 = (1 << 30) - 1, _31 = (1u << 31) - 1;

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u64;
  raw_t v_;
  CEXP mint_2e61n1() : v_{} {}
  CEXP mint_2e61n1(int_c auto v) : v_{mod(v)} {}
  // clang-format off
  template <uint_c T>
  static CEXP raw_t mod(T x) { return x < MOD ? (raw_t)x : (x = T(((raw_t)x & MOD) + ((raw_t)x >> 61))) >= MOD ? x - MOD : (raw_t)x; }
  template <sint_c T>
  static CEXP raw_t mod(T x) { return x >= 0 ? mod(to_uint_t<T>(x)) : MOD - mod(to_uint_t<T>(-x)); }
  // clang-format on
  static CEXP raw_t mod() { return MOD; }
  CEXP raw_t val() const { return v_; }
  CEXP raw_t &data() { return v_; }
  template <class mint>
  CEXP auto neg() const { return mint(MOD - val()); }
  CEXP void add(mint_2e61n1 CR r) { data() = mod(val() + r.val()); }
  CEXP void sub(mint_2e61n1 CR r) { val() < r.val() ? data() = mod(val() + MOD - r.val()) : data() -= r.val(); }
  CEXP void mul(mint_2e61n1 CR r) {
    raw_t au = val() >> 31, ad = val() & _31, bu = r.val() >> 31, bd = r.val() & _31, _ = ad * bu + au * bd;
    data() = mod(((au * bu) << 1) + ad * bd + ((_ & _30) << 31) + (_ >> 30));
  }
};

}  // namespace tifa_libs::math

#endif