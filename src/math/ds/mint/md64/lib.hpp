#pragma once

#include "../../../../nt/mod/montgomery64/lib.hpp"
#include "../_base/lib.hpp"

namespace tifa_libs {

template <i64 ID>
class mint_md64_tag : public mint_impl_::mint_tag_base {
  static inline montgomery64<0> core;

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u64 m) NE { core.reset(m); }

 protected:
  using raw_t = u64;
  raw_t v_{};
  CEXP mint_md64_tag() NE = default;
  CEXP mint_md64_tag(int_c auto v) NE : v_{mod(v)} {}

 public:
  static CEXP raw_t mod(int_c auto v) NE { return core.redc_mul(core.norm(i64(v % (std::conditional_t<sint_c<decltype(v)>, i64, u64>)mod())), core.R2); }
  static CEXP raw_t mod() NE { return core.MOD; }
  CEXP raw_t val() CNE {
    raw_t res = -core.mul_h(v_ * core.R, mod());
    return res + (mod() & -(res >> 63));
  }
  CEXP raw_t& data() NE { return v_; }

 protected:
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    res.v_ = (mod() & -raw_t(v_ != 0)) - v_;
    return res;
  }
  CEXP void add(mint_md64_tag CR r) NE { v_ += r.v_ - mod(), v_ += mod() & -(v_ >> 63); }
  CEXP void sub(mint_md64_tag CR r) NE { v_ -= r.v_, v_ += mod() & -(v_ >> 63); }
  CEXP void mul(mint_md64_tag CR r) NE { v_ = core.redc_mul(v_, r.v_); }
};
template <i64 ID>
using mint_md64 = mint_impl_::mint<mint_md64_tag<ID>>;

}  // namespace tifa_libs
