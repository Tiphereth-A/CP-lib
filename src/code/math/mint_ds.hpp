#ifndef TIFALIBS_MATH_MINT_DS
#define TIFALIBS_MATH_MINT_DS

#include "mint.hpp"

namespace tifa_libs::math {

template <i32 ID>
class mint_ds : public mint<mint_ds<ID>, u32> {
  using base = mint<mint_ds<ID>, u32>;
  friend base;

  struct barrett {
    u32 m_;
    u64 im;
    // @param m `1 <= m < 2^31`
    explicit CEXP barrett(u32 m = 998244353) : m_(m), im(-1_u64 / m + 1) {}
    // @return m
    CEXP u32 umod() const { return m_; }
    CEXP u32 mul(u32 a, u32 b) const {
      u64 z = (u64)a * b, x = (u64)(((u128)z * im) >> 64);
      u32 v = (u32)(z - x * m_);
      return v + (m_ <= v ? m_ : 0);
    }
  };

  static inline barrett bt_;

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u32 m) {
    assert(1 <= m);
    bt_ = barrett(m);
  }

  CEXP mint_ds() {}
  template <int_c T>
  CEXP mint_ds(T v) { this->v_ = mod_(v); }

 private:
  using raw_t = TPN base::raw_type;
  using sraw_t = TPN base::sraw_type;
  template <sint_c T>
  static CEXP raw_t mod_(T v) {
    i64 x = i64(v % (i64)mod_());
    return raw_t(x + (x < 0 ? mod_() : 0));
  }
  template <uint_c T>
  static CEXP raw_t mod_(T v) { return raw_t(v % mod_()); }
  static CEXP raw_t mod_() { return bt_.umod(); }
  CEXP raw_t val_() const { return this->v_; }
  CEXP raw_t &data_() { return this->v_; }

  CEXP mint_ds neg_() const { return -(sraw_t)val_(); }
  CEXP mint_ds &adde_(mint_ds CR r) {
    data_() += r.val_();
    if (val_() >= mod_()) data_() -= mod_();
    return *this;
  }
  CEXP mint_ds &sube_(mint_ds CR r) {
    data_() -= r.val_();
    if (val_() >= mod_()) data_() += mod_();
    return *this;
  }
  CEXP mint_ds &mule_(mint_ds CR r) {
    data_() = bt_.mul(val_(), r.val_());
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif