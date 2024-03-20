#ifndef TIFALIBS_ENUM_ENUM_SUPSET
#define TIFALIBS_ENUM_ENUM_SUPSET

#include "../util/util.hpp"

namespace tifa_libs {

// enumerate x : x \in {n} and x \superset b
template <u32 = 0>
class enum_supset {
  static inline u32 b_, n_;
  u32 now_;

  static constexpr u32 num_begin() { return b_; }
  static constexpr u32 num_end() { return 1_u32 << n_; }

 public:
  static constexpr void set(u32 b, u32 n) {
    assert((u32)std::countl_one(b) <= n && n < 32);
    b_ = b, n_ = n;
  }
  static constexpr enum_supset begin() { return num_begin(); }
  static constexpr enum_supset end() { return num_end(); }

  constexpr enum_supset(u32 now = num_begin()) : now_(now) { assert(now <= num_end()); }

  constexpr u32 operator*() const { return now_; }
  constexpr bool operator!=(enum_supset const& x) const { return **this != *x; }
  constexpr void operator++() { now_ = std::min((now_ + 1) | b_, num_end()); }
};

}  // namespace tifa_libs

#endif