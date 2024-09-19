#ifndef TIFALIBS_MATH_MINT_S63
#define TIFALIBS_MATH_MINT_S63

#include "mint.hpp"

namespace tifa_libs::math {

template <u64 MOD>
class mint_s63 : public mint<mint_s63<MOD>, u64> {
  using base = mint<mint_s63<MOD>, u64>;
  friend base;

  static CEXP u64 R = []() {
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    return iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv, iv * (t - MOD * iv);
  }();
  static CEXP u64 R2 = []() {
    u64 iv = -MOD % MOD;
    for (u32 i = 0; i != 64; ++i)
      if ((iv *= 2) >= MOD) iv -= MOD;
    return iv;
  }();

  static_assert(MOD & 1);
  static_assert(R * MOD == 1);
  static_assert((MOD >> 63) == 0);
  static_assert(MOD != 1);

  static CEXP u64 mulh(u64 x, u64 y) {
    u64 a = x >> 32, b = (u32)(x), c = y >> 32, d = (u32)(y), ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) + (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static CEXP u64 redc_mul(u64 x, u64 y) {
    u64 res = mulh(x, y) - mulh(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static CEXP u64 norm(i64 x) { return (u64)x + (MOD & -(x < 0)); }

 public:
  static CEXP bool FIXED_MOD = true;
  CEXP mint_s63() {}
  template <int_c T>
  CEXP mint_s63(T v) { this->v_ = mod_(v); }

 private:
  using raw_t = TPN base::raw_t;
  using sraw_t = TPN base::sraw_t;
  template <int_c T>
  static CEXP raw_t mod_(T v) { return redc_mul(norm(i64(v % (std::conditional_t<sint_c<T>, i64, u64>)mod_())), R2); }
  static CEXP raw_t mod_() { return MOD; }
  CEXP raw_t val_() const {
    raw_t res = -mulh(this->v_ * R, mod_());
    return res + (MOD & -(res >> 63));
  }
  CEXP raw_t &data_() { return this->v_; }

  CEXP mint_s63 neg_() const {
    mint_s63 res;
    return res.v_ = (MOD & -(this->v_ != 0)) - this->v_, res;
  }
  CEXP mint_s63 &adde_(mint_s63 CR r) { return this->v_ += r.v_ - MOD, this->v_ += MOD & -(this->v_ >> 63), *this; }
  CEXP mint_s63 &sube_(mint_s63 CR r) { return this->v_ -= r.v_, this->v_ += MOD & -(this->v_ >> 63), *this; }
  CEXP mint_s63 &mule_(mint_s63 CR r) { return this->v_ = redc_mul(this->v_, r.v_), *this; }
};

}  // namespace tifa_libs::math

#endif