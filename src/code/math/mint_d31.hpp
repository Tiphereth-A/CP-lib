#ifndef TIFALIBS_MATH_MINT_D31
#define TIFALIBS_MATH_MINT_D31

#include "mint.hpp"

namespace tifa_libs::math {

template <int ID>
class mint_d31 : public mint<mint_d31<ID>, u32> {
  using base = mint<mint_d31<ID>, u32>;
  friend base;

  static inline u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;

  static CEXP u32 norm(i32 x) { return u32(x + (-(x < 0) & (i32)MOD)); }
  static CEXP u32 redc(u64 x) {
    u32 t = u32((x + u64((u32)x * R) * MOD_ODD) >> 32);
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static CEXP u32 tsf(u32 x) { return redc(u64(x % MOD_ODD) * R2) << OFFSET | (x & MASK); }

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u32 m) {
    assert(!(m == 1 || m >> 31));
    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD /= 2);
    MASK = (1_u32 << OFFSET) - 1_u32;
    u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
    iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv;
    R = iv * (MOD_ODD * iv - t);
    R2 = u32(-u64(MOD_ODD) % MOD_ODD);
  }

  CEXP mint_d31() {}
  template <int_c T>
  CEXP mint_d31(T v) { this->v_ = mod_(v); }

 private:
  using raw_t = TPN base::raw_type;
  using sraw_t = TPN base::sraw_type;
  template <int_c T>
  static CEXP raw_t mod_(T v) { return tsf(norm(i32(v % (std::conditional_t<sint_c<T>, i32, u32>)mod_()))); }
  static CEXP raw_t mod_() { return MOD; }
  CEXP raw_t val_() const {
    raw_t h = redc(this->v_ >> OFFSET);
    return ((h - this->v_) * R & MASK) * MOD_ODD + h;
  }
  CEXP raw_t &data_() { return this->v_; }

  CEXP mint_d31 neg_() const {
    mint_d31 res;
    raw_t h = this->v_ >> OFFSET;
    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-this->v_ & MASK);
    return res;
  }
  CEXP mint_d31 &adde_(mint_d31 CR r) {
    raw_t h = (this->v_ >> OFFSET) + (r.v_ >> OFFSET) - MOD_ODD;
    this->v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((this->v_ + r.v_) & MASK);
    return *this;
  }
  CEXP mint_d31 &sube_(mint_d31 CR r) {
    raw_t h = (this->v_ >> OFFSET) - (r.v_ >> OFFSET);
    this->v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((this->v_ - r.v_) & MASK);
    return *this;
  }
  CEXP mint_d31 &mule_(mint_d31 CR r) {
    this->v_ = (redc((u64)(this->v_ >> OFFSET) * (r.v_ >> OFFSET)) << OFFSET) | ((this->v_ * r.v_) & MASK);
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif