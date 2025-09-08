#ifndef TIFALIBS_MATH_MINT_D31
#define TIFALIBS_MATH_MINT_D31

#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <u64 ID>
class mint_d31 {
  static inline u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;
  static CEXP u32 norm(i32 x) NE { return u32(x + (-(x < 0) & (i32)MOD)); }
  static CEXP u32 redc(u64 x) NE {
    u32 t = u32((x + u64((u32)x * R) * MOD_ODD) >> 32);
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static CEXP u32 tsf(u32 x) NE { return redc(u64(x % MOD_ODD) * R2) << OFFSET | (x & MASK); }

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u32 m) NE {
    for (assert(!(m == 1 || m >> 31)), MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD /= 2);
    MASK = (1_u32 << OFFSET) - 1_u32;
    u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
    iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv, R = iv * (MOD_ODD * iv - t), R2 = u32(-u64(MOD_ODD) % MOD_ODD);
  }

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_d31() NE = default;
  CEXP mint_d31(int_c auto v) NE : v_{mod(v)} {}
  template <int_c T>
  static CEXP raw_t mod(T v) NE { return tsf(norm(i32(v % (std::conditional_t<sint_c<T>, i32, u32>)mod()))); }
  static CEXP raw_t mod() NE { return MOD; }
  CEXP raw_t val() CNE {
    raw_t h = redc(v_ >> OFFSET);
    return ((h - v_) * R & MASK) * MOD_ODD + h;
  }
  CEXP raw_t &data() NE { return v_; }
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    raw_t h = v_ >> OFFSET;
    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_ & MASK);
    return res;
  }
  CEXP void add(mint_d31 CR r) NE {
    raw_t h = (v_ >> OFFSET) + (r.v_ >> OFFSET) - MOD_ODD;
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ + r.v_) & MASK);
  }
  CEXP void sub(mint_d31 CR r) NE {
    raw_t h = (v_ >> OFFSET) - (r.v_ >> OFFSET);
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - r.v_) & MASK);
  }
  CEXP void mul(mint_d31 CR r) NE { v_ = (redc((u64)(v_ >> OFFSET) * (r.v_ >> OFFSET)) << OFFSET) | ((v_ * r.v_) & MASK); }
};

}  // namespace tifa_libs::math

#endif