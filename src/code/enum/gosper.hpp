#ifndef TIFALIBS_ENUM_GOSPER
#define TIFALIBS_ENUM_GOSPER

#include "../bit/lowbit.hpp"

namespace tifa_libs {

template <u32 = 0>
class gosper {
  static inline u32 n_, k_;
  u64 now_;

  static CEXP u64 num_begin() { return (1_u64 << k_) - 1; }
  static CEXP u64 num_end() { return 1_u64 << n_; }

 public:
  static CEXP void set(u32 n, u32 k) {
    assert(k && k <= n && n < 64);
    n_ = n;
    k_ = k;
  }
  static CEXP gosper begin() { return num_begin(); }
  static CEXP gosper end() { return num_end(); }

  CEXP gosper(u64 now = num_begin()) : now_(min(now, num_end())) { assert(now == num_end() || (u32)std::popcount(now) == k_); }

  CEXP u64 operator*() const { return now_; }
  CEXP bool operator!=(gosper CR x) const { return **this != *x; }
  CEXP void operator++() {
    u64 c = bit::lowbit(now_), r = now_ + c;
    now_ = min(((r ^ now_) / 4 / c) | r, num_end());
  }
};

}  // namespace tifa_libs

#endif