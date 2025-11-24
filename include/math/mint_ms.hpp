#ifndef TIFALIBS_MATH_MINT_MS
#define TIFALIBS_MATH_MINT_MS

#include "../nt/montgomery.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <u64 MOD_>
class mint_ms {
  static_assert(MOD_ <= UINT32_MAX);
  using core = montgomery<MOD_>;

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_ms() NE = default;
  CEXP mint_ms(int_c auto v) NE : v_{mod(v)} {}
  static CEXP raw_t mod(sint_c auto v) NE { return core::reduce(u64(i32(v % (i32)mod()) + (i32)mod()) * core::R2); }
  static CEXP raw_t mod(uint_c auto v) NE { return core::reduce(u64(v % mod()) * core::R2); }
  static CEXP raw_t mod() NE { return MOD_; }
  CEXP raw_t val() CNE { return core::norm(core::reduce(v_)); }
  CEXP raw_t& data() NE { return v_; }
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    res.v_ = (core::MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  CEXP void add(mint_ms CR r) NE { v_ += r.v_ - core::MOD2, v_ += core::MOD2 & -(v_ >> 31); }
  CEXP void sub(mint_ms CR r) NE { v_ -= r.v_, v_ += core::MOD2 & -(v_ >> 31); }
  CEXP void mul(mint_ms CR r) NE { v_ = core::reduce(u64(v_) * r.v_); }
};

}  // namespace tifa_libs::math

#endif