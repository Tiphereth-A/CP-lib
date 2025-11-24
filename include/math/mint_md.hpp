#ifndef TIFALIBS_MATH_MINT_MD
#define TIFALIBS_MATH_MINT_MD

#include "../nt/montgomery.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <u64 ID>
class mint_md {
  static inline montgomery<0> core;

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u32 m) NE { core.reset(m); }

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_md() NE = default;
  CEXP mint_md(int_c auto v) NE : v_{mod(v)} {}
  static CEXP raw_t mod(int_c auto v) NE { return core.tsf(core.norm(i32(v % (std::conditional_t<sint_c<decltype(v)>, i32, u32>)mod()))); }
  static CEXP raw_t mod() NE { return core.MOD; }
  CEXP raw_t val() CNE {
    raw_t h = core.reduce(v_ >> core.OFFSET);
    return ((h - v_) * core.R & core.MASK) * core.MOD_ODD + h;
  }
  CEXP raw_t& data() NE { return v_; }
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    raw_t h = v_ >> core.OFFSET;
    res.v_ = (((core.MOD_ODD & -(h != 0)) - h) << core.OFFSET) | (-v_ & core.MASK);
    return res;
  }
  CEXP void add(mint_md CR r) NE {
    raw_t h = (v_ >> core.OFFSET) + (r.v_ >> core.OFFSET) - core.MOD_ODD;
    v_ = ((h + (core.MOD_ODD & -(h >> 31))) << core.OFFSET) | ((v_ + r.v_) & core.MASK);
  }
  CEXP void sub(mint_md CR r) NE {
    raw_t h = (v_ >> core.OFFSET) - (r.v_ >> core.OFFSET);
    v_ = ((h + (core.MOD_ODD & -(h >> 31))) << core.OFFSET) | ((v_ - r.v_) & core.MASK);
  }
  CEXP void mul(mint_md CR r) NE { v_ = (core.reduce((u64)(v_ >> core.OFFSET) * (r.v_ >> core.OFFSET)) << core.OFFSET) | ((v_ * r.v_) & core.MASK); }
};

}  // namespace tifa_libs::math

#endif