#ifndef TIFALIBS_ENUM_GOSPER
#define TIFALIBS_ENUM_GOSPER

#include "../bit/lowbit.hpp"

namespace tifa_libs {

template <u32 ID = 0>
class Gosper {
  static inline u32 n_, k_;
  u64 now_;

  static constexpr u64 num_begin() { return (1_u64 << k_) - 1; }
  static constexpr u64 num_end() { return 1_u64 << n_; }

 public:
  static constexpr void set(u32 n, u32 k) {
    assert(k && k <= n && n < 64);
    n_ = n;
    k_ = k;
  }
  static constexpr Gosper begin() { return num_begin(); }
  static constexpr Gosper end() { return num_end(); }

  constexpr Gosper(u64 now = num_begin()) : now_(std::min(now, num_end())) { assert(now == num_end() || (u32)std::popcount(now) == k_); }

  constexpr u64 operator*() const { return now_; }
  constexpr bool operator!=(Gosper const &x) const { return **this != *x; }
  constexpr void operator++() {
    u64 c = bit::lowbit(now_), r = now_ + c;
    now_ = std::min(((r ^ now_) / 4 / c) | r, num_end());
  }
};

}  // namespace tifa_libs

#endif