#pragma once

#include "../../../../nt/mod/montgomery/lib.hpp"
#include "../_base/lib.hpp"

namespace tifa_libs {

template <i64 ID>
class mint_md_tag : public mint_impl_::mint_tag_base {
  static inline montgomery<0> core;

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u32 m) NE { core.reset(m); }

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_md_tag() NE = default;
  CEXP mint_md_tag(int_c auto v) NE : v_{mod(v)} {}

 public:
  static CEXP raw_t mod(sint_c auto v) NE { retif_((v >= 0) [[likely]], mod((to_uint_t<decltype(v)>)v), core.tsf(core.norm(i32(v % (i32)mod())))); }
  static CEXP raw_t mod(uint_c auto v) NE {
    if CEXP (umost64_c<decltype(v)>) {
      retif_((u64 x = (u64)v; x < mod()) [[likely]], core.tsf((raw_t)x), core.tsf((raw_t)(x % mod())));
    } else retif_((v < mod()) [[likely]], core.tsf((raw_t)v), core.tsf((raw_t)(v % mod())));
  }
  static CEXP raw_t mod() NE { return core.MOD; }
  CEXP raw_t val() CNE {
    retif_((!core.OFFSET) [[likely]], core.reduce(v_));
    raw_t h = core.reduce(v_ >> core.OFFSET);
    return ((h - v_) * core.R & core.MASK) * core.MOD_ODD + h;
  }
  CEXP raw_t& data() NE { return v_; }

 protected:
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    if (!core.OFFSET) [[likely]] {
      res.v_ = (core.MOD_ODD & -raw_t(v_ != 0)) - v_;
      return res;
    }
    raw_t h = v_ >> core.OFFSET;
    res.v_ = (((core.MOD_ODD & -raw_t(h != 0)) - h) << core.OFFSET) | (-v_ & core.MASK);
    return res;
  }
  CEXP void add(mint_md_tag CR r) NE {
    if (!core.OFFSET) [[likely]] {
      raw_t h = v_ + r.v_ - core.MOD_ODD;
      v_ = h + (core.MOD_ODD & -(h >> 31));
      return;
    }
    raw_t h = (v_ >> core.OFFSET) + (r.v_ >> core.OFFSET) - core.MOD_ODD;
    v_ = ((h + (core.MOD_ODD & -(h >> 31))) << core.OFFSET) | ((v_ + r.v_) & core.MASK);
  }
  CEXP void sub(mint_md_tag CR r) NE {
    if (!core.OFFSET) [[likely]] {
      raw_t h = v_ - r.v_;
      v_ = h + (core.MOD_ODD & -(h >> 31));
      return;
    }
    raw_t h = (v_ >> core.OFFSET) - (r.v_ >> core.OFFSET);
    v_ = ((h + (core.MOD_ODD & -(h >> 31))) << core.OFFSET) | ((v_ - r.v_) & core.MASK);
  }
  CEXP void mul(mint_md_tag CR r) NE {
    if (!core.OFFSET) [[likely]] {
      v_ = core.reduce((u64)v_ * r.v_);
      return;
    }
    v_ = (core.reduce((u64)(v_ >> core.OFFSET) * (r.v_ >> core.OFFSET)) << core.OFFSET) | ((v_ * r.v_) & core.MASK);
  }
};
template <i64 ID>
using mint_md = mint_impl_::mint<mint_md_tag<ID>>;

}  // namespace tifa_libs
