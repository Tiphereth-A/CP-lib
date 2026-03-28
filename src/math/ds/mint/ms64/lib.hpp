#pragma once

#include "../../../../nt/mod/montgomery64/lib.hpp"
#include "../_base/lib.hpp"

namespace tifa_libs {

template <u64 MOD>
class mint_ms64_tag : public mint_impl_::mint_tag_base {
  using core = montgomery64<MOD>;

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u64;
  raw_t v_{};
  CEXP mint_ms64_tag() NE = default;
  CEXP mint_ms64_tag(int_c auto v) NE : v_{mod(v)} {}

 public:
  template <int_c T>
  static CEXP raw_t mod(T v) NE { return core::redc_mul(core::norm(i64(v % (std::conditional_t<sint_c<T>, i64, u64>)mod())), core::R2); }
  static CEXP raw_t mod() NE { return MOD; }
  CEXP raw_t val() CNE {
    raw_t res = -core::mulh(this->v_ * core::R, mod());
    return res + (mod() & -(res >> 63));
  }
  CEXP raw_t& data() NE { return v_; }

 protected:
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    res.v_ = (mod() & -raw_t(this->v_ != 0)) - v_;
    return res;
  }
  CEXP void add(mint_ms64_tag CR r) NE { v_ += r.v_ - mod(), v_ += mod() & -(this->v_ >> 63); }
  CEXP void sub(mint_ms64_tag CR r) NE { v_ -= r.v_, v_ += mod() & -(this->v_ >> 63); }
  CEXP void mul(mint_ms64_tag CR r) NE { v_ = core::redc_mul(this->v_, r.v_); }
};
template <u64 MOD>
using mint_ms64 = mint_impl_::mint<mint_ms64_tag<MOD>>;

}  // namespace tifa_libs
