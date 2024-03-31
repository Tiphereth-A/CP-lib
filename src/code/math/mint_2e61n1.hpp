#ifndef TIFALIBS_MATH_MINT_2E61N1
#define TIFALIBS_MATH_MINT_2E61N1

#include "mint.hpp"

namespace tifa_libs::math {

class mint_2e61n1 : public mint<mint_2e61n1, u64> {
  using base = mint<mint_2e61n1, u64>;
  friend base;

  static constexpr u64 MOD = (1ull << 61) - 1;
  static constexpr u64 _30 = (1 << 30) - 1, _31 = (1u << 31) - 1;

 public:
  static constexpr bool FIXED_MOD = true;
  constexpr mint_2e61n1() {}
  template <int_c T>
  constexpr mint_2e61n1(T v) { this->v_ = mod_(v); }

 private:
  using raw_t = typename base::raw_type;
  using sraw_t = typename base::sraw_type;
  // clang-format off
  template <uint_c T>
  static constexpr raw_t mod_(T x) { return x < MOD ? (raw_t)x : (x = T(((raw_t)x & MOD) + ((raw_t)x >> 61))) >= MOD ? x - MOD : (raw_t)x; }
  template <sint_c T>
  static constexpr raw_t mod_(T x) { return x >= 0 ? mod_(to_uint_t<T>(x)) : MOD - mod_(to_uint_t<T>(-x)); }
  // clang-format on
  static constexpr raw_t mod_() { return MOD; }
  constexpr raw_t val_() const { return this->v_; }
  constexpr raw_t &data_() { return this->v_; }

  constexpr mint_2e61n1 neg_() const { return mint_2e61n1(MOD - val_()); }
  constexpr mint_2e61n1 &adde_(mint_2e61n1 const &r) {
    data_() = mod_(val_() + r.val_());
    return *this;
  }
  constexpr mint_2e61n1 &sube_(mint_2e61n1 const &r) {
    val_() < r.val_() ? data_() = mod_(val_() + MOD - r.val_()) : data_() -= r.val_();
    return *this;
  }
  constexpr mint_2e61n1 &mule_(mint_2e61n1 const &r) {
    raw_t au = val_() >> 31, ad = val_() & _31, bu = r.val_() >> 31, bd = r.val_() & _31, _ = ad * bu + au * bd;
    data_() = mod_(((au * bu) << 1) + ad * bd + ((_ & _30) << 31) + (_ >> 30));
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif