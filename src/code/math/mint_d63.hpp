#ifndef TIFALIBS_MATH_MINT_D63
#define TIFALIBS_MATH_MINT_D63

#include "mint.hpp"

namespace tifa_libs::math {

template <int ID>
class mint_d63 : public mint<mint_d63<ID>, u64> {
  using base = mint<mint_d63<ID>, u64>;
  friend base;

  static inline u64 MOD, R, R2;

  static CEXP u64 mul_h(u64 x, u64 y) {
    u64 a = x >> 32, b = (u32)x, c = y >> 32, d = (u32)y, ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) + (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static CEXP u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_h(x, y) - mul_h(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static CEXP u64 norm(i64 x) { return u64(x + i64(MOD & u64(-(x < 0)))); }

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u64 m) {
    assert(!((m & 1) == 0 || m == 1 || m >> 63));
    MOD = m;
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv, R = iv * (t - MOD * iv), R2 = -MOD % MOD;
    flt_ (u32, i, 0, 64)
      if ((R2 *= 2) >= MOD) R2 -= MOD;
  }

  CEXP mint_d63() {}
  template <int_c T>
  CEXP mint_d63(T v) { this->v_ = mod_(v); }

 private:
  using raw_t = TPN base::raw_type;
  using sraw_t = TPN base::sraw_type;
  template <int_c T>
  static CEXP raw_t mod_(T v) { return redc_mul(norm(i64(v % (std::conditional_t<sint_c<T>, i64, u64>)mod_())), R2); }
  static CEXP raw_t mod_() { return MOD; }
  CEXP raw_t val_() const {
    raw_t res = -mul_h(this->v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  CEXP raw_t &data_() { return this->v_; }
  CEXP mint_d63 neg_() const {
    mint_d63 res;
    return res.v_ = (MOD & -(this->v_ != 0)) - this->v_, res;
  }
  CEXP mint_d63 &adde_(mint_d63 CR r) { return this->v_ += r.v_ - MOD, this->v_ += MOD & -(this->v_ >> 63), *this; }
  CEXP mint_d63 &sube_(mint_d63 CR r) { return this->v_ -= r.v_, this->v_ += MOD & -(this->v_ >> 63), *this; }
  CEXP mint_d63 &mule_(mint_d63 CR r) { return this->v_ = redc_mul(this->v_, r.v_), *this; }
};

}  // namespace tifa_libs::math

#endif