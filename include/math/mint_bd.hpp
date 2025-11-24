#ifndef TIFALIBS_MATH_MINT_BD
#define TIFALIBS_MATH_MINT_BD

#include "../nt/barrett.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <u64 ID>
class mint_bd {
  static inline barrett<0> core;

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u32 m) NE { core.reset(m); }

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_bd() NE = default;
  CEXP mint_bd(int_c auto v) NE : v_{mod(v)} {}
  static CEXP raw_t mod(sint_c auto v) NE {
    if (v >= 0) return mod((to_uint_t<decltype(v)>)v);
    if (auto ret = mod((to_uint_t<decltype(v)>)-v); ret) return mod() - ret;
    else return ret;
  }
  static CEXP raw_t mod(uint_c auto v) NE {
    if CEXP (umost64_c<decltype(v)>) return core.reduce((u64)v);
    else if (v < UINT64_MAX) return core.reduce((u64)v);
    else return raw_t(v % mod());
  }
  static CEXP raw_t mod() NE { return core.mod; }
  CEXP raw_t val() CNE { return v_; }
  CEXP raw_t& data() NE { return v_; }
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    if (v_) res.v_ = mod() - v_;
    return res;
  }
  CEXP void add(mint_bd CR r) NE {
    if ((v_ += r.v_) >= mod()) v_ -= mod();
  }
  CEXP void sub(mint_bd CR r) NE {
    if (i32(v_ -= r.v_) < 0) v_ += mod();
  }
  CEXP void mul(mint_bd CR r) NE { v_ = core.reduce(u64(v_) * r.v_); }
};

}  // namespace tifa_libs::math

#endif