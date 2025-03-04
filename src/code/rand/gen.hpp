#ifndef TIFALIBS_RAND_GEN
#define TIFALIBS_RAND_GEN

#include "../util/consts.hpp"

namespace tifa_libs::rand {

template <class T>
requires std::is_arithmetic_v<T>
class Gen {
  using res_t = std::conditional_t<sizeof(T) <= 4, u32, u64>;
  using res_wt = std::conditional_t<sizeof(T) <= 4, u64, u128>;
  // clang-format off
  struct mt19937_param { static CEXP u32 w = 32, n = 624, m = 397, r = 31, a = 0x9908b0df, u = 11, d = 0xffffffff, s = 7, b = 0x9d2c5680, t = 15, c = 0xefc60000, l = 18, f = 1812433253; };
  struct mt19937_64_param { static CEXP u64 w = 64, n = 312, m = 156, r = 31, a = 0xb5026f5aa96619e9, u = 29, d = 0x5555555555555555, s = 17, b = 0x71d67fffeda60000, t = 37, c = 0xfff7eee000000000, l = 43, f = 6364136223846793005; };
  using pm = std::conditional_t<std::is_same_v<res_t, u32>, mt19937_param, mt19937_64_param>;
  // clang-format on
  T a_, b_;

  res_t x_[pm::n];
  u32 p_;
  CEXP void gen() NE {
    CEXP res_t um = (~res_t()) << pm::r, lm = ~um;
    res_t _;
    flt_ (res_t, i, p_ = 0, pm::n - pm::m) _ = ((x_[i] & um) | (x_[i + 1] & lm)), x_[i] = (x_[i + pm::m] ^ (_ >> 1) ^ ((_ & 1) ? pm::a : 0));
    flt_ (res_t, i, pm::n - pm::m, pm::n - 1) _ = ((x_[i] & um) | (x_[i + 1] & lm)), x_[i] = (x_[i + (pm::m - pm::n)] ^ (_ >> 1) ^ ((_ & 1) ? pm::a : 0));
    _ = ((x_[pm::n - 1] & um) | (x_[0] & lm)), x_[pm::n - 1] = (x_[pm::m - 1] ^ (_ >> 1) ^ ((_ & 1) ? pm::a : 0));
  }

 public:
  CEXPE Gen(T a = std::numeric_limits<T>::min(), T b = std::numeric_limits<T>::max(), res_t sd = (res_t)TIME) NE : a_(a), b_(b) { assert(a < b || (std::is_integral_v<T> && a == b)), seed(sd); }

  CEXP void range(T min, T max) NE { assert(min < max || (std::is_integral_v<T> && min == max)), a_ = min, b_ = max; }
  void seed() NE { seed((res_t)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()); }
  CEXP void seed(res_t sd) NE {
    x_[0] = sd & gen_max();
    flt_ (res_t, i, 1, p_ = pm::n) x_[i] = ((x_[i - 1] ^ (x_[i - 1] >> (pm::w - 2))) * pm::f + i % pm::n) & gen_max();
  }
  CEXP res_t gen_min() CNE { return 0; }
  CEXP res_t gen_max() CNE { return sizeof(res_t) * 8 == pm::w ? ~res_t() : ((res_t)1 << pm::w) - 1; }
  CEXP res_t next() NE {
    if (p_ >= pm::n) gen();
    res_t _ = x_[p_++];
    _ ^= (_ >> pm::u) & pm::d, _ ^= (_ << pm::s) & pm::b, _ ^= (_ << pm::t) & pm::c, _ ^= (_ >> pm::l);
    return _;
  }
  CEXP T operator()() NE {
    if CEXP (std::integral<T>) {
      res_wt r = (res_wt)b_ - (res_wt)a_ + 1, p = r * next();
      if (res_t l = (res_t)p, _ = res_t(res_wt(-(res_t)r) % r); l < r)
        while (l < _) l = res_t(p = r * next());
      return (T)(p >> pm::w) + a_;
    } else return T(next() / (f128)((u128)gen_max() + 1) * (b_ - a_) + a_);
  }
};

}  // namespace tifa_libs::rand

#endif