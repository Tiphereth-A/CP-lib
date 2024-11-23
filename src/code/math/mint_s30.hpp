#ifndef TIFALIBS_MATH_MINT_S30
#define TIFALIBS_MATH_MINT_S30

#include "../util/traits.hpp"

namespace tifa_libs::math {

template <u64 MOD_>
class mint_s30 {
  static_assert(MOD_ <= UINT32_MAX);
  static CEXP u32 MOD = (u32)MOD_;
  static CEXP u32 MOD2 = MOD << 1;
  static CEXP u32 R = []() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    return iv *= t - MOD * iv, iv *= t - MOD * iv, iv * (MOD * iv - t);
  }();
  static CEXP u32 R2 = -(u64)(MOD) % MOD;
  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);
  static CEXP u32 reduce(u64 x) { return u32((x + u64((u32)x * R) * MOD) >> 32); }
  static CEXP u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u32;
  raw_t v_;
  CEXP mint_s30() : v_{} {}
  CEXP mint_s30(int_c auto v) : v_{mod(v)} {}
  static CEXP raw_t mod(sint_c auto v) { return reduce(u64(v % (i32)mod() + (i32)mod()) * R2); }
  static CEXP raw_t mod(uint_c auto v) { return reduce(u64(v % mod()) * R2); }
  static CEXP raw_t mod() { return MOD; }
  CEXP raw_t val() const { return norm(reduce(v_)); }
  CEXP raw_t &data() { return v_; }
  template <class mint>
  CEXP auto neg() const {
    mint res;
    return res.v_ = (MOD2 & -(v_ != 0)) - v_, res;
  }
  CEXP void add(mint_s30 CR r) { v_ += r.v_ - MOD2, v_ += MOD2 & -(v_ >> 31); }
  CEXP void sub(mint_s30 CR r) { v_ -= r.v_, v_ += MOD2 & -(v_ >> 31); }
  CEXP void mul(mint_s30 CR r) { v_ = reduce(u64(v_) * r.v_); }
};

}  // namespace tifa_libs::math

#endif