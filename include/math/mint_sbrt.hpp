#ifndef TIFALIBS_MATH_MINT_SBRT
#define TIFALIBS_MATH_MINT_SBRT

#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <u64 MOD_>
class mint_sbrt {
  static_assert(MOD_ && MOD_ <= UINT32_MAX);
  static CEXP u32 MOD = MOD_;
  static CEXP u64 R = (~(u64)MOD + 1) / MOD + 1;

  static CEXP u32 redc(u64 a) NE {
    if (u64 q = u64((u128)a * R >> 64); (a -= q * MOD) >= MOD) a -= MOD;
    return (u32)a;
  }

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_sbrt() NE = default;
  CEXP mint_sbrt(int_c auto v) NE : v_{mod(v)} {}
  static CEXP raw_t mod(sint_c auto v) NE {
    if (v >= 0) return mod((to_uint_t<decltype(v)>)v);
    return raw_t(v % (i32)mod()) + mod();
  }
  static CEXP raw_t mod(uint_c auto v) NE {
    if CEXP (umost64_c<decltype(v)>) return redc((u64)v);
    else return raw_t(v % mod());
  }
  static CEXP raw_t mod() NE { return MOD; }
  CEXP raw_t val() CNE { return v_; }
  CEXP raw_t& data() NE { return v_; }
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    if (v_) res.v_ = MOD - v_;
    return res;
  }
  CEXP void add(mint_sbrt CR r) NE {
    if ((v_ += r.v_) >= MOD) v_ -= MOD;
  }
  CEXP void sub(mint_sbrt CR r) NE {
    if (i32(v_ -= r.v_) < 0) v_ += MOD;
  }
  CEXP void mul(mint_sbrt CR r) NE { v_ = redc(u64(v_) * r.v_); }
};

}  // namespace tifa_libs::math

#endif