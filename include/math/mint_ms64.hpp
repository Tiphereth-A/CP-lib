#ifndef TIFALIBS_MATH_MINT_MS64
#define TIFALIBS_MATH_MINT_MS64

#include "../nt/montgomery64.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <u64 MOD>
class mint_ms64 {
  using core = montgomery64<MOD>;

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u64;
  raw_t v_{};
  CEXP mint_ms64() NE = default;
  CEXP mint_ms64(int_c auto v) NE : v_{mod(v)} {}
  template <int_c T>
  static CEXP raw_t mod(T v) NE { return core::redc_mul(core::norm(i64(v % (std::conditional_t<sint_c<T>, i64, u64>)mod())), core::R2); }
  static CEXP raw_t mod() NE { return MOD; }
  CEXP raw_t val() CNE {
    raw_t res = -core::mulh(this->v_ * core::R, mod());
    return res + (mod() & -(res >> 63));
  }
  CEXP raw_t& data() NE { return v_; }
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    res.v_ = (mod() & -(this->v_ != 0)) - v_;
    return res;
  }
  CEXP void add(mint_ms64 CR r) NE { v_ += r.v_ - mod(), v_ += mod() & -(this->v_ >> 63); }
  CEXP void sub(mint_ms64 CR r) NE { v_ -= r.v_, v_ += mod() & -(this->v_ >> 63); }
  CEXP void mul(mint_ms64 CR r) NE { v_ = core::redc_mul(this->v_, r.v_); }
};

}  // namespace tifa_libs::math

#endif