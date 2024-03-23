#ifndef TIFALIBS_MATH_MINT_S30
#define TIFALIBS_MATH_MINT_S30

#include "mint.hpp"

namespace tifa_libs::math {

template <u32 MOD>
class mint_s30 : public mint<mint_s30<MOD>, u32> {
  using base = mint<mint_s30<MOD>, u32>;
  friend base;

  static constexpr u32 MOD2 = MOD << 1;
  static constexpr u32 R = []() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }();
  static constexpr u32 R2 = -(u64)(MOD) % MOD;

  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);

  static constexpr u32 reduce(u64 x) { return u32((x + u64((u32)x * R) * MOD) >> 32); }
  static constexpr u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

 public:
  static constexpr bool FIXED_MOD = true;
  constexpr mint_s30() {}
  template <int_c T>
  constexpr mint_s30(T v) { this->v_ = mod_(v); }

 private:
  using raw_t = typename base::raw_type;
  using sraw_t = typename base::sraw_type;
  template <sint_c T>
  static constexpr raw_t mod_(T v) { return reduce(u64(v % (i32)mod_() + (i32)mod_()) * R2); }
  template <uint_c T>
  static constexpr raw_t mod_(T v) { return reduce(u64(v % mod_()) * R2); }
  static constexpr raw_t mod_() { return MOD; }
  constexpr raw_t val_() const { return norm(reduce(this->v_)); }
  constexpr raw_t &data_() { return this->v_; }

  constexpr mint_s30 neg_() const {
    mint_s30 res;
    res.v_ = (MOD2 & -(this->v_ != 0)) - this->v_;
    return res;
  }
  constexpr mint_s30 &adde_(mint_s30 const &r) {
    this->v_ += r.v_ - MOD2, this->v_ += MOD2 & -(this->v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &sube_(mint_s30 const &r) {
    this->v_ -= r.v_, this->v_ += MOD2 & -(this->v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &mule_(mint_s30 const &r) {
    this->v_ = reduce(u64(this->v_) * r.v_);
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif