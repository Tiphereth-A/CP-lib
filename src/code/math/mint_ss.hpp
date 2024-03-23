#ifndef TIFALIBS_MATH_MINT_SS
#define TIFALIBS_MATH_MINT_SS

#include "mint.hpp"

namespace tifa_libs::math {

template <u32 MOD>
class mint_ss : public mint<mint_ss<MOD>, u32> {
  using base = mint<mint_ss<MOD>, u32>;
  friend base;
  static_assert(MOD >= 1);

 public:
  static constexpr bool FIXED_MOD = true;
  constexpr mint_ss() {}
  template <int_c T>
  constexpr mint_ss(T v) { this->v_ = mod_(v); }

 private:
  using raw_t = typename base::raw_type;
  using sraw_t = typename base::sraw_type;
  template <sint_c T>
  static constexpr raw_t mod_(T v) {
    i64 x = i64(v % (i64)mod_());
    return raw_t(x + (x < 0 ? mod_() : 0));
  }
  template <uint_c T>
  static constexpr raw_t mod_(T v) { return raw_t(v % mod_()); }
  static constexpr raw_t mod_() { return MOD; }
  constexpr raw_t val_() const { return this->v_; }
  constexpr raw_t &data_() { return this->v_; }

  constexpr mint_ss neg_() const { return -(sraw_t)val_(); }
  constexpr mint_ss &adde_(mint_ss const &r) {
    data_() += r.val_();
    if (val_() >= mod_()) data_() -= mod_();
    return *this;
  }
  constexpr mint_ss &sube_(mint_ss const &r) {
    data_() -= r.val_();
    if (val_() >= mod_()) data_() += mod_();
    return *this;
  }
  constexpr mint_ss &mule_(mint_ss const &r) {
    data_() = u32((u64)val_() * r.val_() % mod_());
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif