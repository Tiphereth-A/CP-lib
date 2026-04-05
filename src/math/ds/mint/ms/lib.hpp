#pragma once

#include "../../../../nt/mod/montgomery/lib.hpp"
#include "../_base/lib.hpp"

namespace tifa_libs {

template <u64 MOD_>
class mint_ms_tag : public mint_impl_::mint_tag_base {
  static_assert(MOD_ <= UINT32_MAX);
  using core = montgomery<MOD_>;

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_ms_tag() NE = default;
  CEXP mint_ms_tag(int_c auto v) NE : v_{mod(v)} {}

 public:
  static CEXP raw_t mod(sint_c auto v) NE {
    if CEXP (smost64_c<decltype(v)>) {
      retif_((v >= 0 && (u64)v < mod()) [[likely]], core::reduce(u64((raw_t)v) * core::R2));
    }
    return core::reduce(u64(i32(v % (i32)mod()) + (i32)mod()) * core::R2);
  }
  static CEXP raw_t mod(uint_c auto v) NE {
    if CEXP (umost64_c<decltype(v)>) {
      retif_((u64 x = (u64)v; x < mod()) [[likely]], core::reduce(x * core::R2), core::reduce(u64(x % mod()) * core::R2));
    } else retif_((v < mod()) [[likely]], core::reduce(u64((raw_t)v) * core::R2), core::reduce(u64((raw_t)(v % mod())) * core::R2));
  }
  static CEXP raw_t mod() NE { return MOD_; }
  CEXP raw_t val() CNE { return core::norm(core::reduce(v_)); }
  CEXP raw_t& data() NE { return v_; }

 protected:
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    res.v_ = (core::MOD2 & -raw_t(v_ != 0)) - v_;
    return res;
  }
  CEXP void add(mint_ms_tag CR r) NE { v_ += r.v_ - core::MOD2, v_ += core::MOD2 & -(v_ >> 31); }
  CEXP void sub(mint_ms_tag CR r) NE { v_ -= r.v_, v_ += core::MOD2 & -(v_ >> 31); }
  CEXP void mul(mint_ms_tag CR r) NE { v_ = core::reduce(u64(v_) * r.v_); }
};
template <u64 MOD>
using mint_ms = mint_impl_::mint<mint_ms_tag<MOD>>;

}  // namespace tifa_libs
