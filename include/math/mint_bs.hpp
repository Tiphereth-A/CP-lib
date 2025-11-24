#ifndef TIFALIBS_MATH_MINT_BS
#define TIFALIBS_MATH_MINT_BS

#include "../nt/barrett.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <u64 MOD_>
class mint_bs {
  static_assert(MOD_ && MOD_ <= UINT32_MAX);
  using core = barrett<MOD_>;

 public:
  static CEXP bool FIXED_MOD = true;

 protected:
  using raw_t = u32;
  raw_t v_{};
  CEXP mint_bs() NE = default;
  CEXP mint_bs(int_c auto v) NE : v_{mod(v)} {}
  static CEXP raw_t mod(sint_c auto v) NE {
    if (v >= 0) return mod((to_uint_t<decltype(v)>)v);
    if (auto ret = mod((to_uint_t<decltype(v)>)-v); ret) return mod() - ret;
    else return ret;
  }
  static CEXP raw_t mod(uint_c auto v) NE {
    if CEXP (umost64_c<decltype(v)>) return core::reduce((u64)v);
    else if (v < UINT64_MAX) return core::reduce((u64)v);
    else return raw_t(v % mod());
  }
  static CEXP raw_t mod() NE { return MOD_; }
  CEXP raw_t val() CNE { return v_; }
  CEXP raw_t& data() NE { return v_; }
  template <class mint>
  CEXP auto neg() CNE {
    mint res;
    if (v_) res.v_ = mod() - v_;
    return res;
  }
  CEXP void add(mint_bs CR r) NE {
    if ((v_ += r.v_) >= mod()) v_ -= mod();
  }
  CEXP void sub(mint_bs CR r) NE {
    if (i32(v_ -= r.v_) < 0) v_ += mod();
  }
  CEXP void mul(mint_bs CR r) NE { v_ = core::reduce(u64(v_) * r.v_); }
};

}  // namespace tifa_libs::math

#endif