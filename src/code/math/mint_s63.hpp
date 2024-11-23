#ifndef TIFALIBS_MATH_MINT_S63
#define TIFALIBS_MATH_MINT_S63

#include "../util/traits.hpp"

namespace tifa_libs::math {

template <u64 MOD>
class mint_s63 {
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

 protected:
  using raw_t = u64;
  raw_t v_;
  CEXP mint_s63() : v_{} {}
  CEXP mint_s63(int_c auto v) : v_{mod(v)} {}
  template <int_c T>
  static CEXP raw_t mod(T v) { return redc_mul(norm(i64(v % (std::conditional_t<sint_c<T>, i64, u64>)mod())), R2); }
  static CEXP raw_t mod() { return MOD; }
  CEXP raw_t val() const {
    raw_t res = -mulh(this->v_ * R, mod());
    return res + (MOD & -(res >> 63));
  }
  CEXP raw_t &data() { return v_; }
  template <class mint>
  CEXP auto neg() const {
    mint res;
    return res.v_ = (MOD & -(this->v_ != 0)) - v_, res;
  }
  CEXP void add(mint_s63 CR r) { v_ += r.v_ - MOD, v_ += MOD & -(this->v_ >> 63); }
  CEXP void sub(mint_s63 CR r) { v_ -= r.v_, v_ += MOD & -(this->v_ >> 63); }
  CEXP void mul(mint_s63 CR r) { v_ = redc_mul(this->v_, r.v_); }
};

}  // namespace tifa_libs::math

#endif